"use strict"
class Process{
  constructor(id, name, time){
    this.id = id
    this.name = name
    this.time = time
  }
}

var process_objects = []

var shell = require('shelljs');
var processes = shell.exec('ps -lx',{silent: true});
processes = processes.split('\n');
processes.forEach(function(process){
  process = process.trim().split(/\s+/);
  var process_object = new Process(process[1],process[14], process[13])
  process_objects.push(process_object)
})
