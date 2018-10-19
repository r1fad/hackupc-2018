"use strict"

var _ = require('lodash');

class Process{
  constructor(id, name, start, etime){
    this.id = id
    this.name = name
    this.start = start
    this.etime = etime
  }
}

var process_objects = []

var shell = require('shelljs');
var processes = shell.exec('ps -eo pid,start,etime,comm | grep /Applications/',{silent: true});
processes = processes.split('\n');
processes.forEach(function(process){
  process = process.trim().split(/\s+/);
  var process_name = process.slice(3,process.length)
  process_name = process_name.join("").trim().split("/")
  var process_name1 = process_name[process_name.length-1]
  if (process_name1.includes('Helper'))
    return
  var process_object = new Process(process[0],process_name1, process[1], process[2])
  process_objects.push(process_object)
})

console.log(process_objects)
