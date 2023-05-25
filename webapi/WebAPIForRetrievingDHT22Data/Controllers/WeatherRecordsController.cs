using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebAPIForRetrievingDHT22Data.Models;

namespace WebAPIForRetrievingDHT22Data.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class WeatherRecordsController : ControllerBase
    {
        private readonly WeatherRecordsContext _context;

        public WeatherRecordsController(WeatherRecordsContext context)
        {
            _context = context;
        }

        // GET: api/WeatherRecords
        [HttpGet]
        public async Task<ActionResult<IEnumerable<WeatherRecord>>> GetWeatherRecords()
        {
          if (_context.WeatherRecords == null)
          {
              return NotFound();
          }
            return await _context.WeatherRecords.ToListAsync();
        }

        // GET: api/WeatherRecords/5
        [HttpGet("{id}")]
        public async Task<ActionResult<WeatherRecord>> GetWeatherRecord(long id)
        {
          if (_context.WeatherRecords == null)
          {
              return NotFound();
          }
            var weatherRecord = await _context.WeatherRecords.FindAsync(id);

            if (weatherRecord == null)
            {
                return NotFound();
            }

            return weatherRecord;
        }

        // PUT: api/WeatherRecords/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutWeatherRecord(long id, WeatherRecord weatherRecord)
        {
            if (id != weatherRecord.Id)
            {
                return BadRequest();
            }

            _context.Entry(weatherRecord).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!WeatherRecordExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/WeatherRecords
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<WeatherRecord>> PostWeatherRecord(WeatherRecord weatherRecord)
        {
          if (_context.WeatherRecords == null)
          {
              return Problem("Entity set 'WeatherRecordsContext.WeatherRecords'  is null.");
          }
            _context.WeatherRecords.Add(weatherRecord);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetWeatherRecord", new { id = weatherRecord.Id }, weatherRecord);
        }

        // DELETE: api/WeatherRecords/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteWeatherRecord(long id)
        {
            if (_context.WeatherRecords == null)
            {
                return NotFound();
            }
            var weatherRecord = await _context.WeatherRecords.FindAsync(id);
            if (weatherRecord == null)
            {
                return NotFound();
            }

            _context.WeatherRecords.Remove(weatherRecord);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool WeatherRecordExists(long id)
        {
            return (_context.WeatherRecords?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
