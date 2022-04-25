import { Modal } from "react-bootstrap/Modal";
("use strict");

const root = ReactDOM.createRoot(document.getElementById("like_button_container"));

function showAlert() {
  <Modal show={true}>
    <Modal.Header closeButton>
      <Modal.Title>Modal heading</Modal.Title>
    </Modal.Header>
    <Modal.Body>Woohoo, you're reading this text in a modal!</Modal.Body>
    <Modal.Footer>
      <Button variant="secondary" onClick={handleClose}>
        Close
      </Button>
      <Button variant="primary" onClick={handleClose}>
        Save Changes
      </Button>
    </Modal.Footer>
  </Modal>;
}
const Button = () => {
  return (
    <button onClick={showAlert} className="button">
      Generate Countdown
    </button>
  );
};

const element = <Button />;
root.render(element);
