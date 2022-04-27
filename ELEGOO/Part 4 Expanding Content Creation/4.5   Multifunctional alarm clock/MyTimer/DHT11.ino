static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void update_dht11_value()
{
  float tem_temperature;
  float tem_humidity;
  
  if( measure_environment( &tem_temperature, &tem_humidity ) == true )
  {
    temperature = tem_temperature;
    humidity = tem_humidity;
  }
}
