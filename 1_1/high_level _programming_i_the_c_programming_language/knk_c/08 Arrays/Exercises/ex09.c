/* Computes average temperature for a month */

#define DAYS_IN_MONTH 30
#define HOURS_IN_DAY 24

int main(void) {
    int temperature_readings[DAYS_IN_MONTH][HOURS_IN_DAY];
    double average_daily_temperature[DAYS_IN_MONTH] = {}, average_hourly_temperature[HOURS_IN_DAY] = {};
    double average_monthly_temperature = 0.00;

    for (int day = 0; day < DAYS_IN_MONTH; ++day) {
        for (int hour = 0; hour < HOURS_IN_DAY; ++hour) {
            average_daily_temperature[day] += average_hourly_temperature[hour];
        }
        average_daily_temperature[day] /= HOURS_IN_DAY;
        average_monthly_temperature += average_daily_temperature[day];
    }
    average_monthly_temperature /= DAYS_IN_MONTH;

    return 0;
}
