/////////////////////////////////////
///  MAX17261 Driver for ESPHome ///
///     By Adagio_Leopard       ///
///    www.hailthebean.com     ///
/////////////////////////////////

#define i2c_addr 0x36
#define VEmpty 0x3a //The Vempty register sets thresholds related to empty detection during operation.
#define DesignCap 0x18 //The DesignCap register holds the expected capacity of the cell.
#define ModelCfg 0xdb //The ModelCFG register controls basic options of the EZ algorithm.
#define IChgTerm 0x1e //The IChgTerm register allows the device to detect when a charge cycle of the cell has completed.
#define FullSOCThr 0x13 //The FullSOCThr register gates detection of end-of-charge. 
#define RComp0 0x38 //The RComp0 register holds characterization information critical to computing the open circuit voltage of a cell under loaded conditions.
#define TempCo 0x39 //The TempCo register holds temperature compensation information for the RComp0 register value.
#define RepCap 0x05 //RepCap or reported remaining capacity in mAh. This register is protected from making sudden jumps during load changes.
#define AtAvCap 0xdf //The AtAvCap register holds the estimated remaining capacity of the cell based on the theoretical load current value of the AtRate register.
#define RepSOC 0x06 //RepSOC is the reported state-of-charge percentage output for use by the application GUI.
#define AtAvSOC 0xde //The AtAvSOC register holds the theoretical state of charge of the cell based on the theoretical load of the AtRate register.
#define FullCapRep 0x10 //This register reports the full capacity that goes with RepCap, generally used for reporting to the GUI. Most applications should only monitor FullCapRep, instead of FullCap or FullCapNom
#define FullCap 0x35 //FullCap is the full discharge capacity compensated according to the present conditions
#define FullCapNom 0x23 //FullCap is the full discharge capacity compensated according to the present conditions
#define TTE 0x11 //The TTE register holds the estimated time to empty for the application under present temperature and load conditions. 
#define AtTTE 0xDD //The AtTTE register can be used to estimate time to empty for any theoretical load entered into the AtRate register.
#define TTF 0x20 //The TTF register holds the estimated time to full for the application under present conditions. 
#define Cycles 0x17 //The Cycles register maintains a total count of the number of charge/discharge cycles of the cell that have occurred.
#define Status 0x00 //The Status register maintains all flags related to alert thresholds and battery insertion or removal.
#define Age 0x07 //The Age register contains a calculated percentage value of the application’s present cell capacity compared to its original design capacity.
#define TimerH 0xbe //TimerH and Timer provide a long-duration time count since last POR.
#define RCell 0x14 //The RCell register provides the calculated internal resistance of the cell.
#define VRipple 0xbc //The VRipple register holds the slow average RMS ripple value of VCell register reading variation compared to the AvgVCell register.
#define AtRate 0x04 //Host software should write the AtRate register with a negative two’s-complement 16-bit value of a theoretical load current prior to reading any of the at-rate output registers (AtTTE, AtAvSOC, AtAvCap).
#define FilterCfg 0x29 //The FilterCfg register sets the average time period for all A/D readings, for mixing OCV results and coulomb-count results
#define RelaxCfg 0x2a //The RelaxCfg register defines how the IC detects whether the cell is in a relaxed state with a low dV/dt. 
#define LearnCfg 0x28 //The LearnCfg register controls all functions relating to adaptation during operation. Table 17 shows the register format.
#define MiscCfg 0x2b //The MiscCfg control register enables various other functions of the device.
#define ConvgCfg 0x49 //The ConvgCfg register configures operation of the converge-to-empty feature.
#define RippleCfg 0xbd //The RippleCfg register configures ripple measurement and ripple compensation.
#define VFSOC 0xff //The VFSOC register holds the calculated present state of charge of the battery according to the voltage fuel gauge
#define FStat 0x3d //The FStat register is a read-only register that monitors the status of the ModelGauge m5 algorithm. Table 20 is the FStat register format.


#include "esphome.h"


class cMax17261 : public PollingComponent, public Sensor 
{

private:
int getBatterySOC()
{
	return 0;
}

unsigned int setCurrentGain (int shuntRes_u)
{
	//Current Register = Current A/D Reading × (CGain Register / 0400h) + COff Register
	unsigned int reg_val = shuntRes_u/1000;
	reg_val /= 1024;
	
	return (reg_val);
	
}

bool getChDc()
{
	return 0;
}


public:

Sensor *battery_percentage = new Sensor();
Sensor *battery_cycles = new Sensor();

///constructor
cMax17261() : PollingComponent(1000){}

float get_setup_priority() const override { return esphome::setup_priority::BUS; }

void setup() override
{
	
}

void update() override
{
	publish_state(setCurrentGain(500));
}
	
};

