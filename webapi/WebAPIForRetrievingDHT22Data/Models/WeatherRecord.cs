﻿namespace WebAPIForRetrievingDHT22Data.Models
{
    public class WeatherRecord
    {
        public long Id { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public DateTime Time { get; set; }
    }
}
