import React, { useState, useEffect } from 'react';

function Weather() {
    const [weatherData, setWeatherData] = useState(null);

    useEffect(() => {
        const fetchWeatherData = async () => {
            const apiKey = 'YOUR_API_KEY';
            const city = 'Orlando';  // You can replace with any city
            const response = await fetch(`https://api.openweathermap.org/data/2.5/forecast?q=${city}&appid=${apiKey}`);
            const data = await response.json();
            setWeatherData(data);
        };

        fetchWeatherData();
    }, []);

    return (
        <div>
            {weatherData ? <Forecast data={weatherData} /> : <p>Loading...</p>}
        </div>
    );
}

export default Weather;
