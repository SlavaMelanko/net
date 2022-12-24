var native = Window.this.MainWindow;

document.ready = function () {
  //document.body.innerText = native.getMessage();
  document.getElementById("quite").onclick = function () {
    native.quite();
  };
};

const labels = ["3AM", "4AM", "5AM", "6AM", "7AM", "8AM"];

const data = {
  labels: labels,
  datasets: [
    {
      label: "One",
      backgroundColor: "rgb(195, 197, 211)",
      borderColor: "rgb(195, 197, 211)",
      data: [60, 25, 35, 20, 15, 5],
      fill: true,
      cubicInterpolationMode: "monotone",
      pointRadius: 0,
      borderWidth: 1,
    },
    {
      label: "Two",
      backgroundColor: "rgb(45, 163, 173)",
      borderColor: "rgb(45, 163, 173)",
      data: [10, 20, 20, 35, 30, 45],
      fill: true,
      cubicInterpolationMode: "monotone",
      pointRadius: 0,
      borderWidth: 1,
    },
  ],
};

const config = {
  type: "line",
  data: data,
  options: {
    responsive: true,
    plugins: {
      title: {
        display: false,
        text: "Chart.js Line Chart",
      },
    },
    interaction: {
      intersect: false,
    },
    scales: {
      x: {
        display: true,
        title: {
          display: true,
          text: "Time",
        },
        grid: {
          display: false,
        },
      },
      y: {
        display: true,
        title: {
          display: true,
          text: "Value",
        },
        grid: {
          display: false,
        },
      },
    },
  },
};
