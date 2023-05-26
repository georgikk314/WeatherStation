using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using System.Diagnostics;
using WeatherStationMVC.Models;

namespace WeatherStationMVC.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public async Task<IActionResult> Index()
        {
            string apiResponse = "";
            List<TemperatureAndHumidity> TempAndHumidity = new List<TemperatureAndHumidity>();
            using (var httpClient = new HttpClient())
            {
                using (var response = await httpClient.GetAsync("http://localhost:5261/api/WeatherRecords"))
                {
                    apiResponse = await response.Content.ReadAsStringAsync();
                    TempAndHumidity = JsonConvert.DeserializeObject<List<TemperatureAndHumidity>>(apiResponse);
                }
            }        


            return View(TempAndHumidity);
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}