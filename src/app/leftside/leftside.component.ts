import { Component, OnInit } from '@angular/core';
import { Message } from '../Message.model';
import { RestService } from '../rest.service'; //The rest service to be able to use HTTP

@Component({
  selector: 'app-leftside',
  templateUrl: './leftside.component.html',
  styleUrls: ['./leftside.component.css']
})
export class LeftsideComponent implements OnInit {

  testString : string = ""; //Teststring (DELETE LATER!!!!!!!!!!!!!)
  postdata : any; //DELETE LATER

  constructor(private REST : RestService) { }

  BlindOpen() { //function to open the window
    this.REST.Open_Close(new Message("windowBlind/open", "ON"))
            .subscribe(data => this.postdata = data);
  }

  BlindClose() { //function to close the window
    this.REST.Open_Close(new Message("windowBlind/close", "ON"))
            .subscribe(data => this.postdata = data);
  }

  TestGET() { //testfunction for GET method
    this.REST.TestServiceGET()
            .subscribe((tempString : string) => (this.testString = tempString));
  }

  ngOnInit(): void { // use it to write out if the connection to the broker has sucessfully made

  }

}
