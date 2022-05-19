import test from 'ava';
import {isHexColor} from '../testUtils/is-hex-color';
import toElectronBackgroundColor from '../../app/utils/to-electron-background-color';

const dc = require('../../app/config/config-default.js');

test('When checking the default config', t => {
  t.true(dc.config.updateChannel === 'stable' || dc.config.updateChannel === 'canary');

  t.true(typeof dc.config.fontSize === 'number');

  t.true(dc.config.fontWeightBold === 'normal' || dc.config.fontWeightBold === 'bold');

  t.true(dc.config.fontWeight === 'normal' || dc.config.fontWeightBold === 'bold');

  t.true(typeof dc.config.lineHeight === 'number');

  t.true(typeof dc.config.letterSpacing === 'number');

  t.true(isHexColor(toElectronBackgroundColor(dc.config.cursorColor)));

  t.true(isHexColor(toElectronBackgroundColor(dc.config.cursorAccentColor)));

  t.true(
    dc.config.cursorShape === 'BEAM' || dc.config.cursorShape === 'UNDERLINE' || dc.config.cursorShape === 'BLOCK'
  );

  t.true(typeof dc.config.cursorBlink === 'boolean');

  t.true(isHexColor(toElectronBackgroundColor(dc.config.foregroundColor)));

  t.true(isHexColor(toElectronBackgroundColor(dc.config.backgroundColor)));

  t.true(isHexColor(toElectronBackgroundColor(dc.config.selectionColor)));

  t.true(isHexColor(toElectronBackgroundColor(dc.config.borderColor)));

  t.true(typeof dc.config.padding === 'string');

  t.true(typeof dc.config.shell === 'string');

  t.true(dc.config.bell === 'SOUND' || dc.config.bell === false);

  t.true(typeof dc.config.copyOnSelect === 'boolean');

  t.true(typeof dc.config.defaultSSHApp === 'boolean');

  t.true(typeof dc.config.quickEdit === 'boolean');

  t.true(dc.config.macOptionSelectionMode === 'vertical' || dc.config.macOptionSelectionMode === 'force');

  t.true(typeof dc.config.webGLRenderer === 'boolean');

  t.true(dc.plugins instanceof Array);

  t.true(dc.localPlugins instanceof Array);

  t.true(typeof dc.keymaps === 'object');
});
