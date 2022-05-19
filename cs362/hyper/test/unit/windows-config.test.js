import test from 'ava';
import {defaults} from '../../app/config/windows.js';

test('when checking "app/config/windows.js"', t => {
  t.true(defaults.windowPosition.length === 2);

  t.true(defaults.windowSize.length === 2);

  t.true(
    defaults.windowPosition.reduce((tt, v) => {
      typeof v === 'number' && tt;
    }, true)
  );

  t.true(
    defaults.windowSize.reduce((tt, v) => {
      typeof v === 'number' && tt;
    }, true)
  );
});
