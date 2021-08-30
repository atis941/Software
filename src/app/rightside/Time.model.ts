export class Time {
    hour:string;
    minute:string;
    hour_and_minute:string;

  constructor(hour:string, minute:string){
    this.hour = hour;
    this.minute = minute;
    this.hour_and_minute = this.toString()
  }

  toString():string {
    return this.hour + ":" + this.minute;
  }

}