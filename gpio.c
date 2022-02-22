#include "gpio.h"
#include "stdint.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction, GPIO_PinPullUP pullup)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			
			SYSCTL_RCGCGPIO_R |= (1<<PORTA_ID);   				
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTA_DIR_R,pin_num);
				
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DIR_R,pin_num);
			}
			if(pullup == ENABLE)
			{
				SET_BIT(GPIO_PORTF_PUR_R,pin_num);
				
			}
			else
			{
				
			}
			GPIO_PORTA_DEN_R |=(1<<pin_num);
			break;
		case PORTB_ID:
			SYSCTL_RCGCGPIO_R |= (1<<PORTB_ID);
			while ((SYSCTL_PRGPIO_R&(1<<PORTB_ID)) == 0){};// allow time for clock to start     				
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTB_DIR_R,pin_num);
				
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DIR_R,pin_num);
			}
			if(pullup == ENABLE)
			{
				SET_BIT(GPIO_PORTB_PUR_R,pin_num);
				
			}
			else
			{
				
			}
			GPIO_PORTB_DEN_R |=(1<<pin_num);
		
			break;
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				
			}
			else
			{
				
			}
			break;
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				
			}
			else
			{
				
			}
			break;
			case PORTE_ID:
			if(direction == PIN_OUTPUT)
			{
				
			}
			else
			{
				
			}
			break;
			case PORTF_ID:
			SYSCTL_RCGCGPIO_R |= (1<<PORTF_ID);
			while ((SYSCTL_PRGPIO_R&(1<<PORTF_ID)) == 0){};// allow time for clock to start
			GPIO_PORTF_LOCK_R = 0x4C4F434B;                // unlock GPIO Port F	
			GPIO_PORTF_CR_R |= (1<<pin_num);               // allow changes to pin_num
      GPIO_PORTF_AMSEL_R = 0x00;                     // disable analog on PF	
      GPIO_PORTF_PCTL_R = 0x00000000;				
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTF_DIR_R,pin_num);
				
			}
			else
			{
				CLEAR_BIT(GPIO_PORTF_DIR_R,pin_num);
			}
			GPIO_PORTF_AFSEL_R = 0x00;
			if(pullup == ENABLE)
			{
				SET_BIT(GPIO_PORTF_PUR_R,pin_num);
				
			}
			else
			{
				
			}
			GPIO_PORTF_DEN_R |=(1<<pin_num);      			
			break;
		}
	}
}




/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTA_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DATA_R,pin_num);
			}
			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTB_DATA_R,pin_num);
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DATA_R,pin_num);
			}
			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
			{
				
			}
			else
			{
				
			}
			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				
			}
			else
			{
				
			}
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			
			break;
		case PORTB_ID:
			
			break;
		case PORTC_ID:
			
			break;
		case PORTD_ID:
			
			break;
		case PORTE_ID:
			
			break;
		case PORTF_ID:
			if(!(GPIO_PORTF_DATA_R&(1<<pin_num))){
				pin_value = LOGIC_LOW;
			}else{
				pin_value = LOGIC_HIGH;
			}
			break;
		}
	}

	return pin_value;
}

/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			SYSCTL_RCGCGPIO_R |= (1<<port_num);
		if(direction == PORT_OUTPUT){
			GPIO_PORTA_DIR_R = 0xFF;		
		}else{
			GPIO_PORTA_DIR_R = 0;
		}
		GPIO_PORTA_DEN_R = 0xFF;
			break;
		case PORTB_ID:
			SYSCTL_RCGCGPIO_R |= (1<<PORTB_ID);
		if(direction == PORT_OUTPUT){
			GPIO_PORTB_DIR_R = 0xFF;		
		}else{
			GPIO_PORTB_DIR_R = 0;
		}
		GPIO_PORTB_DEN_R = 0xFF;
			
			break;
		case PORTC_ID:
			
			break;
		case PORTD_ID:
			
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DATA_R = value;
			break;
		case PORTB_ID:
			GPIO_PORTB_DATA_R = value;
			break;
		case PORTC_ID:
			GPIO_PORTC_DATA_R = value;
			break;
		case PORTD_ID:
			GPIO_PORTD_DATA_R = value;
			break;
		case PORTE_ID:
			GPIO_PORTE_DATA_R = value;
			break;
		case PORTF_ID:
			GPIO_PORTF_DATA_R = value;
			break;
		
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
		
			break;
		case PORTB_ID:
			
			break;
		case PORTC_ID:
			
			break;
		case PORTD_ID:
			
			break;
		}
	}

	return value;
}







