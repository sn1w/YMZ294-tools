Midi = require('@tonejs/midi')
fs = require('fs')
process = require('process')

function calcFrequency(note_number) {

  return Math.floor(440 * (2 ** ((note_number - 69) / 12)));
}

const midiData = fs.readFileSync(process.argv[2])
const midi = new Midi(midiData)

const name = midi.name
//get the tracks
var channel_counter = 0;

var note_arrays = [];

midi.tracks.forEach(track => {
  //tracks have notes and controlChanges

  //notes are an array
  const notes = track.notes
  notes.forEach(note => {
    //note.midi, note.time, note.duration, note.name
    // console.log(`SetFrequency(${channel_counter},${calcFrequency(note.midi)});`)
    // console.log(`delay(${Math.floor(note.duration * 1000)});`)
    // console.log(`SetFrequency(${channel_counter},0);`)
    note_arrays.push({
      ...note,
      time: Math.floor(note.time * 1000),
      channel: channel_counter
    });
  })
  if (notes.length != 0) {
      channel_counter += 1;
  }

  //the control changes are an object
  //the keys are the CC number
  track.controlChanges[64]
  //they are also aliased to the CC number's common name (if it has one)

  // track.controlChanges.sustain.forEach(cc => {
  //   // cc.ticks, cc.value, cc.time
  // })

  //the track also has a channel and instrument
  //track.instrument.name
})

function sortByTime(note1, note2) {
  return note1.time - note2.time;
}

note_arrays.sort((a,b) => {
  return a.time - b.time;
})

for (var i = 0; i < note_arrays.length; i++) {
}

const midi_groups = note_arrays.reduce((result, current) => {
  const element = result.find((p) => p.time === current.time);
  if (element) {
    element.notes.push(
      {
          channel: current.channel,
          midi: current.midi
      }
    )
  } else {
    result.push({
      time: current.time,
      notes: [
        {
          channel: current.channel,
          midi: current.midi
        }
      ]
    });
  }

  return result;
}, []);

for (var i = 1; i < midi_groups.length; i++) {
  var last_element = midi_groups[i - 1];
  var current_time = midi_groups[i].time;

  var sleepDuration = current_time - last_element.time;
  last_element.notes.forEach(note => {
    if (note.channel > 2) {
      return;
    }

    console.log(`SetFrequency(${note.channel},${calcFrequency(note.midi)});`);

  });
  console.log(`delay(${sleepDuration});`);
}

