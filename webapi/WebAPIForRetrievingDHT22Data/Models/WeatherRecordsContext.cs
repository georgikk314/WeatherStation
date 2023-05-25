using Microsoft.EntityFrameworkCore;

namespace WebAPIForRetrievingDHT22Data.Models
{
    public class WeatherRecordsContext : DbContext
    {
        public WeatherRecordsContext(DbContextOptions<WeatherRecordsContext> options) 
            : base (options)
        {     
        }

        public DbSet<WeatherRecord> WeatherRecords { get; set; }
    }
}
