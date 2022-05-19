import test from 'ava';

const bgColor = require('../../app/utils/to-electron-background-color');
test('When calling bgColor', t => {
  //These tests check numerous valid inputs to the function
  t.is(bgColor('red'), '#FF0000');

  t.is(bgColor('rgb(255,0,0)'), '#FF0000');

  t.is(bgColor('#FF0000'), '#FF0000');

  t.is(bgColor('#FF000050'), '#4fFF0000');

  //This test feeds junk data, and tests for a color parsing error
  const error = t.throws(() => {
    bgColor('asdf');
  }, Error);
  t.is(error.message, 'Unable to parse color from string: asdf');
});

const {getColorMap} = require('../../app/utils/colors');
test('When calling getColorMap', t => {
  //This test checks for valid function output given a valid input
  t.deepEqual(
    getColorMap([
      '#000000',
      '#FF0000',
      '#00FF00',
      '#FFFF00',
      '#0000FF',
      '#FF00FF',
      '#00FFFF',
      '#FFFFFF',
      '#555555',
      '#FF8080',
      '#80FF80',
      '#FFFF80',
      '#8080FF',
      '#FF80FF',
      '#80FFFF',
      '#AAAAAA',
      '#55AAFF',
      '#808080'
    ]),
    {
      black: '#000000',
      blue: '#0000FF',
      colorCubes: '#55AAFF',
      cyan: '#00FFFF',
      grayscale: '#808080',
      green: '#00FF00',
      lightBlack: '#555555',
      lightBlue: '#8080FF',
      lightCyan: '#80FFFF',
      lightGreen: '#80FF80',
      lightMagenta: '#FF80FF',
      lightRed: '#FF8080',
      lightWhite: '#AAAAAA',
      lightYellow: '#FFFF80',
      magenta: '#FF00FF',
      red: '#FF0000',
      white: '#FFFFFF',
      yellow: '#FFFF00'
    }
  );

  //This test checks the output when the input is a single color
  t.is(getColorMap('##FF0000'), '##FF0000');

  //This test checks the output when the input is incomplete
  t.deepEqual(getColorMap(['#000000', '#FF0000', '#00FF00']), {
    black: '#000000',
    red: '#FF0000',
    green: '#00FF00'
  });

  //This test checks the output when an integer is provided
  t.is(getColorMap(255), 255);

  //This test checks for valid function output given a more input colors than expected
  t.deepEqual(
    getColorMap([
      '#000000',
      '#FF0000',
      '#00FF00',
      '#FFFF00',
      '#0000FF',
      '#FF00FF',
      '#00FFFF',
      '#FFFFFF',
      '#555555',
      '#FF8080',
      '#80FF80',
      '#FFFF80',
      '#8080FF',
      '#FF80FF',
      '#80FFFF',
      '#AAAAAA',
      '#55AAFF',
      '#808080',
      '#FFBBAA',
      '#11FF33'
    ]),
    {
      black: '#000000',
      blue: '#0000FF',
      colorCubes: '#55AAFF',
      cyan: '#00FFFF',
      grayscale: '#808080',
      green: '#00FF00',
      lightBlack: '#555555',
      lightBlue: '#8080FF',
      lightCyan: '#80FFFF',
      lightGreen: '#80FF80',
      lightMagenta: '#FF80FF',
      lightRed: '#FF8080',
      lightWhite: '#AAAAAA',
      lightYellow: '#FFFF80',
      magenta: '#FF00FF',
      red: '#FF0000',
      white: '#FFFFFF',
      yellow: '#FFFF00'
    }
  );
});
