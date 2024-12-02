import React from 'react';

function Forecast({ data }) {
    return (
        <div>
            <h2>7-Day Weather Forecast</h2>
            {data.list.slice(0, 7).map((day, index) => (
                <div key={index}>
                    <p>Date: {new Date(day.dt * 1000).toLocaleDateString()}</p>
                    <p>Temperature: {Math.round(day.main.temp - 273.15)}°C</p>
                    <p>Weather: {day.weather[0].description}</p>
                </div>
            ))}
        </div>
    );
}

export default Forecast;
