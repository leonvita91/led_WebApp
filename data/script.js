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

// slider brightness
const slider = document.getElementById("myBright");
const output = document.querySelector(".bright-value");
output.textContent = slider.value;

slider.addEventListener("input", function() {
  output.textContent = this.value;
});

// slider fps
const fps = document.getElementById("myFrame");
const out = document.querySelector(".frame-value");
out.textContent = fps.value;

fps.addEventListener("input", function() {
  out.textContent = this.value;
});

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

// Target Blue button
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