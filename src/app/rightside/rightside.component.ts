import { Component, OnInit } from '@angular/core';
import { Time } from "./Time.model";

@Component({
  selector: 'app-rightside',
  templateUrl: './rightside.component.html',
  styleUrls: ['./rightside.component.css']
})


export class RightsideComponent implements OnInit {

  hourTemp:string = '';
  minuteTemp:string = '';

  registered_Times: Time[] = [];

  ngOnInit(): void {
  }

  hourInput(event: any): void {
    this.hourTemp = event.target.value;
  }

  minuteInput(event: any): void{
    this.minuteTemp = event.target.value;
  }

  addNewTime(): void{
    if(this.hourTemp != '' && this.minuteTemp != ''){
      this.registered_Times.push(new Time(this.hourTemp,this.minuteTemp));
    }else{
      //warning, invalid Time as Input
    }
  }

  
}
