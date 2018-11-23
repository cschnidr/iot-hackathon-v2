#include "mgos.h"
#include "mgos_mqtt.h"
#include "mgos_dht.h"
#ifdef MGOS_HAVE_WIFI
#include "mgos_wifi.h"
#endif

static struct mgos_dht *s_dht = NULL;

static void led_timer_cb(void *arg) {
  bool val = mgos_gpio_toggle(mgos_sys_config_get_board_led1_pin());
  LOG(LL_INFO, ("%s uptime: %.2lf, RAM: %lu, %lu free", val ? "Tick" : "Tock",
                mgos_uptime(), (unsigned long) mgos_get_heap_size(),
                (unsigned long) mgos_get_free_heap_size()));
  (void) arg;
}

static void net_cb(int ev, void *evd, void *arg) {
  switch (ev) {
    case MGOS_NET_EV_DISCONNECTED:
      LOG(LL_INFO, ("%s", "Net disconnected"));
      break;
    case MGOS_NET_EV_CONNECTING:
      LOG(LL_INFO, ("%s", "Net connecting..."));
      break;
    case MGOS_NET_EV_CONNECTED:
      LOG(LL_INFO, ("%s", "Net connected"));
      break;
    case MGOS_NET_EV_IP_ACQUIRED:
      LOG(LL_INFO, ("%s", "Net got IP address"));
      break;
  }

  (void) evd;
  (void) arg;
}

static void report_temperature(void *arg) {
  char topic[100], message[160];
  struct json_out out = JSON_OUT_BUF(message, sizeof(message));
   
  time_t now=time(0);
  struct tm *timeinfo = localtime(&now);

  char timestring[30];
  strftime(timestring, 30, "%d.%m.%Y %H:%M", timeinfo);
  
  //Date format example: 2011 03-18 11-25-04 Fri = "%Y %m-%d %H-%M-%S %a"
  
  //char *timestring = asctime(timeinfo); // preparing time/date string for json below
  //timestring[strlen(timestring) -1 ] = '\0'; // overwrite /n with zero in order to produce a valid json below
 
snprintf(topic, sizeof(topic), "event/temp_humidity");
  //json_printf(&out, "{total_ram: %lu, free_ram: %lu, temperature: %f, humidity: %f, device: \"%s\", timestamp: \"%02d:%02d:%02d\"}",
  json_printf(&out, "{total_ram: %lu, free_ram: %lu, temperature: %f, humidity: %f, device: \"%s\", timestamp: \"%s\"}",
              (unsigned long) mgos_get_heap_size(),
              (unsigned long) mgos_get_free_heap_size(),
              (float) mgos_dht_get_temp(s_dht), 
              (float) mgos_dht_get_humidity(s_dht),
              (char *) mgos_sys_config_get_device_id(),
              (char *) timestring);
  //            (int) timeinfo->tm_hour,
  //            (int) timeinfo->tm_min,
  //            (int) timeinfo->tm_sec);
  bool res = mgos_mqtt_pub(topic, message, strlen(message), 1, false);
  LOG(LL_INFO, ("Published to MQTT: %s", res ? "yes" : "no"));
  
  (void) arg;
}

static void button_cb(int pin, void *arg) {
  float t = mgos_dht_get_temp(s_dht);
  float h = mgos_dht_get_humidity(s_dht);
  LOG(LL_INFO, ("Button presses on pin: %d", pin));
  LOG(LL_INFO, ("Temperature: %f *C Humidity: %f %%\n", t, h));
   
  report_temperature(NULL);
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) {
  char buf[8];
  /* Blink built-in LED every second */
  int led_pin = mgos_sys_config_get_board_led1_pin();
  if (led_pin >= 0) {
    LOG(LL_INFO, ("LED pin %s", mgos_gpio_str(led_pin, buf)));
    mgos_gpio_set_mode(led_pin, MGOS_GPIO_MODE_OUTPUT);
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, led_timer_cb, NULL);
  }

  /* Report temperature to AWS IoT Core every 5 mins */
  mgos_set_timer(300000, MGOS_TIMER_REPEAT, report_temperature, NULL);
 
  /* Publish to MQTT on button press */
  mgos_gpio_set_button_handler(0,
                               MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_NEG, 200,
                               button_cb, NULL);
                                
  if ((s_dht = mgos_dht_create(4, DHT11)) == NULL) { // using Pin4 on ESP8266
    LOG(LL_INFO, ("Unable to initialize DHT11"));
  }
 

  /* Network connectivity events */
  mgos_event_add_group_handler(MGOS_EVENT_GRP_NET, net_cb, NULL);


  return MGOS_APP_INIT_SUCCESS;
}
