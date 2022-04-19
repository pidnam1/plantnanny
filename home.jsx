import React from "react";

import $ from "jquery";

export default class PersonComponent extends React.Component {
  constructor(props) {
    super(props);

    this.state = {
      firstName: "",

      lastName: "",
    };
  }

  componentDidMount() {
    this.fetch();
  }

  fetch() {
    var context = this;
  }

  render() {
    return (
      <div>
        <h1>
          {this.state.firstName} {this.state.LastName}
        </h1>
      </div>
    );
  }
}
