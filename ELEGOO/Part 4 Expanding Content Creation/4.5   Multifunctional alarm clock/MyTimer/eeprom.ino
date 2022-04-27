  void eeprom_write_int(unsigned int address, unsigned int data)
{
    unsigned int dataL = data&0xFF;
    unsigned int dataH = data>>8;
    EEPROM.write(address,   dataL);
    EEPROM.write(address+1, dataH);
}                       
 
unsigned int eeprom_read_int(unsigned int address)
{
    unsigned int dataL = EEPROM.read(address);
    unsigned int dataH = EEPROM.read(address+1);
    return((dataH<<8) + dataL);
}

void eeprom_clear_all(unsigned int eeprom_size)
{
    unsigned int i = 0;
    unsigned char data = 0;
    for (i=0; i<eeprom_size; i++)
    {   
        EEPROM.write(i, data);
    }
}
