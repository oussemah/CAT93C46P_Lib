/* CAT93C46P EEPROM Library Example 
 * This is a sample sketch using the embedded library (eeprom_xxx() functions) allowing reading/writing/erasing CAT93C46P EEPROMs
 * AUTHOR : Oussema HARBI <oussema.elharbi@gmail.com>
 * LICENSE : GPLv2
 */

#define CS_PIN   53
#define DO_PIN   50
#define DI_PIN   51
#define SK_PIN   52

#define SK_HIGH_TIME 1  /* According to datasheet we need more than 200ns */
#define SK_LOW_TIME  1  /* According to datasheet we need more than 200ns */

volatile uint16_t rcp=0;
volatile uint8_t address = 0x00;

void setup() {
  // Prepare Serial Debug
  Serial.begin( 115200);
  
  // Prepare GPIOS
  pinMode( CS_PIN, OUTPUT);
  pinMode( SK_PIN, OUTPUT);
  pinMode( DI_PIN, OUTPUT);
  pinMode( DO_PIN, INPUT);

  eeprom_erase();
  delay(500);
  
  eeprom_write( 31, 17);
  eeprom_write( 12, 24);
  eeprom_write( 25, 98);
  eeprom_write( 43, 117);
  
  delay(500);
  
  Serial.flush();
  Serial.println("------------------------- EEPROM Contents ---------------------------");
}

void loop()
{
  // Read from EEPROM
  rcp = eeprom_read(address);
  
  // Write the read value
  printShort(rcp);
  
  // Increment address
  address++;
  
  if (address % 16 == 0)
  {
    Serial.println("");
    if (address == 64)
    {
      delay(975);
      address = 0;
      Serial.println("------------------------- EEPROM Contents ---------------------------");
    }
  }
  else
    Serial.print(" ");

  // Some delay
  delay( 25);
}

void printShort(uint16_t buf)
{
  if (buf <  4096) {
     Serial.print(0, DEC); 
  }
  if (buf <  256) {
     Serial.print(0, DEC); 
  }
  if (buf <  16) {
     Serial.print(0, DEC); 
  }
  Serial.print(buf, HEX);
}

uint16_t eeprom_read(uint8_t address)
{
  uint16_t toReturn = 0;
  
  digitalWrite( CS_PIN, HIGH);
  eeprom_send_byte((uint8_t) (0x80 | (address & 0x3F)));
  toReturn |= eeprom_read_short();
  digitalWrite( CS_PIN, LOW);
  return toReturn;
}

void eeprom_write_enable()
{
  digitalWrite( CS_PIN, HIGH);

  /* Send start bit*/
  digitalWrite( DI_PIN, HIGH);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0*/
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0 */
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 1 */
  digitalWrite( DI_PIN, HIGH);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 1*/
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);
  
  /* Send 4 random bits */
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( CS_PIN, LOW);      
}

void eeprom_write_disable()
{
  digitalWrite( CS_PIN, HIGH);

  /* Send start bit*/
  digitalWrite( DI_PIN, HIGH);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0*/
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0 */
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0 */
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0*/
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);
  
  /* Send 4 random bits */
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( CS_PIN, LOW);      
}

void eeprom_erase()
{
  eeprom_write_enable();
  
  digitalWrite( CS_PIN, HIGH);

  /* Send start bit*/
  digitalWrite( DI_PIN, HIGH);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0*/
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0 */
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 1 */
  digitalWrite( DI_PIN, HIGH);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_LOW_TIME);

  /* Send 0*/
  digitalWrite( DI_PIN, LOW);
  delay(SK_LOW_TIME);
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  
  /* Send 4 random bits */
  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  digitalWrite( SK_PIN, HIGH);
  delay(SK_HIGH_TIME);
  digitalWrite( SK_PIN, LOW);
  delay(SK_HIGH_TIME);

  /* Wait for erase to finish */
  digitalWrite( CS_PIN, LOW);  
  delay(2 * SK_LOW_TIME);
  digitalWrite( CS_PIN, HIGH);  
  while (digitalRead(DO_PIN) == LOW);
  delay(2 * SK_HIGH_TIME);
  
  digitalWrite( CS_PIN, LOW);    
  
  eeprom_write_disable();
}

void eeprom_write( uint8_t address, uint16_t value)
{
  eeprom_write_enable();

  digitalWrite( CS_PIN, HIGH);
  eeprom_send_byte((uint8_t) (0x40 | (address & 0x3F)));
  eeprom_send_data(value);  
  digitalWrite( CS_PIN, LOW);  

  eeprom_write_disable();
}

void eeprom_send_byte(uint8_t byte_out)
{
    uint8_t byte_in = 0;
    uint8_t thisBit;
    
    /* Shift-out a bit to the MOSI line */
    digitalWrite( DI_PIN, HIGH);
 
    /* Delay for at least the peer's setup time */
    delay(SK_LOW_TIME);
 
    /* Pull the clock line high */
    digitalWrite( SK_PIN, HIGH);
 
    /* Delay for at least the peer's hold time */
    delay(SK_HIGH_TIME);
 
    /* Pull the clock line low */
    digitalWrite( SK_PIN, LOW);
 
    for (thisBit = 0x80; thisBit; thisBit >>= 1) {
        /* Shift-out a bit to the MOSI line */
        digitalWrite( DI_PIN, (byte_out & thisBit) ? HIGH : LOW);
 
        /* Delay for at least the peer's setup time */
        delay(SK_LOW_TIME);
 
        /* Pull the clock line high */
        digitalWrite( SK_PIN, HIGH);
 
        /* Delay for at least the peer's hold time */
        delay(SK_HIGH_TIME);
 
        /* Pull the clock line low */
        digitalWrite( SK_PIN, LOW);
    }
}

void eeprom_send_data(uint16_t short_out)
{
    uint16_t thisBit;
    
    for (thisBit = 0x8000; thisBit; thisBit >>= 1) {
        /* Shift-out a bit to the MOSI line */
        digitalWrite( DI_PIN, (short_out & thisBit) ? HIGH : LOW);
 
        /* Delay for at least the peer's setup time */
        delay(SK_LOW_TIME);
 
        /* Pull the clock line high */
        digitalWrite( SK_PIN, HIGH);
 
        /* Delay for at least the peer's hold time */
        delay(SK_HIGH_TIME);
 
        /* Pull the clock line low */
        digitalWrite( SK_PIN, LOW);
    }
}

uint16_t eeprom_read_short()
{
  uint16_t short_in = 0 ;
  uint16_t thisBit;
  
  while (digitalRead( DO_PIN) == HIGH);
  for (thisBit = 0x8000; thisBit; thisBit >>= 1) {
         /* Pull the clock line high */
        digitalWrite( SK_PIN, HIGH);
 
        /* Shift-in a bit from the MISO line */
        if (digitalRead(DO_PIN) == HIGH)
            short_in |= thisBit;

        /* Delay for at least the peer's hold time */
        delay(SK_HIGH_TIME);
 
        /* Pull the clock line low */
        digitalWrite( SK_PIN, LOW);
        
        /* Delay for at least the peer's setup time */
        delay(SK_LOW_TIME);
    }
    return short_in;
}

