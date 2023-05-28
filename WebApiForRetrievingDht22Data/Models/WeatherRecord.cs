namespace WebApiForRetrievingDht22Data.Models
{
    public class WeatherRecord
    {
        public long Id { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public DateTime Time { get; set; }
        public double HeatIndex { get; set; }
        public double DewTemperature { get; set; }
       
    }
}
