document.addEventListener("DOMContentLoaded", function() {
    console.log("Script loaded!");
});

// Clock 
function updateClock() {
  const now = new Date();
  const hours = now.getHours().toString().padStart(2, '0');
  const minutes = now.getMinutes().toString().padStart(2, '0');
  const seconds = now.getSeconds().toString().padStart(2, '0');

  const timeString = `${hours}:${minutes}:${seconds}`;
  document.getElementById('time').textContent = timeString;
}

// Update the clock every second
setInterval(updateClock, 1000);

// Initial call to display the clock immediately
updateClock();

// ESP temperature
setInterval(() => {
        fetch('/esp_temp')
        .then(response => response.text())
        .then(data => document.getElementById('esp_temp').innerText = data + " °C")
        .catch(error => console.error('Error:', error));
    }, 2000);
    

// ESP CPU Reading
setInterval(() => {
    fetch('/esp_cpu')
        .then(response => response.text())
        .then(data => document.getElementById('cpu_usage').innerText = data + '%')
        .catch(error => console.error('Error:', error));
    }, 2000); // Update every 1 second

// LEDs Section
function updateBrightness(value) {
    // Update the slider value display
    document.getElementById("myBright").textContent = value;
    // Send an HTTP GET request to the server to update the brightness
    fetch(`/brightness?value=${value}`);
    // Update the brightness value display
    const output = document.querySelector(".bright-value");
    output.textContent = value;
}
function updateFrams(value) {
    // Update the slider value dispaly
    document.getElementById("myFrame").textContent = value;

    fetch(`/set-frames?value=${value}`);
    const output = document.querySelector(".frame-value");
    output.textContent = value;
}

// Target Stop button
document.getElementById("stop-light").onclick = function() {
    fetch('/stop-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Blue button
document.getElementById("blue-light").onclick = function() {
    fetch('/blue-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Red button
document.getElementById("red-light").onclick = function() {
    fetch('/red-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Green button
document.getElementById("green-light").onclick = function() {
    fetch('/green-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Animations LED Section

// Target Rainbow button
document.getElementById("rainbow-light").onclick = function() {
    fetch('/rainbow-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Race button
document.getElementById("race-light").onclick = function() {
    fetch('/race-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Race button
document.getElementById("cross-light").onclick = function() {
    fetch('/cross-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Water button
document.getElementById("water-light").onclick = function() {
    fetch('/water-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

// Target Dancing button
document.getElementById("dancing-light").onclick = function() {
    fetch('/dancing-light', {
        method: 'POST'
    })
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(data => {
        console.log(data);
    })
    .catch(error => {
        console.error('There was an error!', error);
    });
};

