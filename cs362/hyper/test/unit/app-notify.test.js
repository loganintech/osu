import test from 'ava';
const testnotif = require('../../app/notify.js');

test('When notify function is used improperly (integrity)', t => {
  var recycledtxt = {};

  t.pass(testnotif.notify(`Test Title1, Test Body1`, recycledtxt));

  t.pass(testnotif.notify(`[1,2,3], This Should Fail`, recycledtxt));

  t.pass(testnotif.notify(`This should fail, [1,2,3]`, recycledtxt));

  t.fail(testnotif.notify(`This should fail, `, recycledtxt));

  t.pass(testnotif.notify(`[1,2,3], [1,2,3]`, recycledtxt));

  t.pass(testnotif.notify(`This, should work`));
});
