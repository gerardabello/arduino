// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
#ifdef ESP8266
    extern "C" {
        #include "user_interface.h"
    }
#endif

#include <Arduino.h>

ADC_MODE(ADC_TOUT);

#define num_samples 512
uint16_t adc_addr[num_samples]; // point to the address of ADC continuously fast sampling output
uint16_t adc_num = num_samples; // sampling number of ADC continuously fast sampling, range [1, 65535]
uint8_t adc_clk_div = 16; // ADC working clock = 80M/adc_clk_div, range [8, 32], the recommended value is 8

int i = 0;
unsigned long start = 0;
unsigned long total = 0;
unsigned long tim = 0;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop() {
    // put your main code here, to run repeatedly:
    #ifdef ESP8266
        // Serial.println(system_get_sdk_version());

        wifi_set_opmode(NULL_MODE);
        system_soft_wdt_stop();
        ets_intr_lock( ); //close interrupt
        noInterrupts();

        start = micros();

        // Serial.println(system_adc_read());
        system_adc_read_fast(adc_addr, adc_num, adc_clk_div);

        unsigned int tot = micros() - start;

        interrupts();
        ets_intr_unlock(); //open interrupt
        system_soft_wdt_restart();

        tim += tot;
        total += num_samples * 1000000.0 / tot;
        i++;

        for (int j=0; j<adc_num;  j++) {
            //Serial.println(adc_addr[j]);
        }

        if (i == 100) {
            Serial.print("Sampling rate: ");
            Serial.println(total / 100);
            Serial.print("It lasted: ");
            Serial.println(tim / 100);

            i = 0;
            tim = 0;
            total = 0;
        }
    #endif
}
