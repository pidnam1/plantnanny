let modal;
document.addEventListener("click", (e) => {
  if (e.target.className === "btn modal-open") {
    modal = document.getElementById(e.target.dataset.id);
    openModal(modal);
  } else if (e.target.className === "modal-close") {
    closeModal(modal);
  } else {
    return;
  }
});

document.addEventListener("click", (j) => {
  if (j.target.className === "submit_values") {
    console.log("working");
    let elem1 = document.getElementById("list_temp");
    let elem2 = document.getElementById("list_light");
    let elem3 = document.getElementById("list_soil");

    let temperature_min = document.getElementById("temperature_input_min").value;
    let temperature_max = document.getElementById("temperature_input_max").value;
    let light_min = document.getElementById("light_input_min").value;
    let light_max = document.getElementById("light_input_max").value;
    let soil_min = document.getElementById("soil_input_min").value;
    let soil_max = document.getElementById("soil_input_max").value;

    elem1 = "Temperature: " + temperature_min.toString() + " - " + temperature_max.toString();
    elem2 = "Light Level%: " + light_min.toString() + " - " + light_max.toString();
    elem3 = "Soil Moisture%: " + soil_min.toString() + " - " + soil_max.toString();

    document.getElementById("list_temp").innerHTML = elem1;
    document.getElementById("list_light").innerHTML = elem2;
    document.getElementById("list_soil").innerHTML = elem3;

    //document.getElementById("form_id").reset();
    //document.getElementById("temperature_input").value = "";
    //document.getElementById("light_input").value = "";
    //document.getElementById("soil_input").value = "";
  }
});

const openModal = (modal) => {
  document.body.style.overflow = "hidden";
  modal.setAttribute("open", "true");
  document.addEventListener("keydown", escClose);
  let overlay = document.createElement("div");
  overlay.id = "modal-overlay";
  document.body.appendChild(overlay);
};

const closeModal = (modal) => {
  document.body.style.overflow = "auto";
  modal.removeAttribute("open");
  document.removeEventListener("keydown", escClose);
  document.body.removeChild(document.getElementById("modal-overlay"));
};

const escClose = (e) => {
  if (e.keyCode == 27) {
    closeModal();
  }
};
