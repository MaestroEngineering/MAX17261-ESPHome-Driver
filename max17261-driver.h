/////////////////////////////////////
///  MAX17261 Driver for ESPHome ///
///     By Adagio_Leopard       ///
///    www.hailthebean.com     ///
/////////////////////////////////

#include "esphome.h"

class cMax17261 : public PollingComponent, public Sensor 
{

private:
int getBatterySOC()
{
	return 0;
}

bool getChDc()
{
	return 0;
}


public:

///constructor
cMax17261() : PollingComponent(1000){}

float get_setup_priority() const override { return esphome::setup_priority::BUS; }

void setup() override
{
	
}

void update() override
{
	publish_state(42.0);
}
	
};