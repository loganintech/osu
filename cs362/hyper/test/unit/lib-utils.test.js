import test from 'ava';

const last = require('../../lib/utils/array');
test('When calling last([1, 2, 3]) result should be 3', t => {
  let res = last([1, 2, 3]);

  t.true(res == 3);
});

const isExecutable = require('../../lib/utils/file');
test('When calling isExecutable', t => {
  t.true(
    isExecutable({
      mode: 0o0700
    })
  );
  t.true(
    isExecutable({
      mode: 0o0070
    })
  );
  t.true(
    isExecutable({
      mode: 0o0007
    })
  );

  // These should all fail, but don't
  t.false(
    isExecutable({
      mode: 0o0666
    })
  );
  t.false(
    isExecutable({
      mode: 0o0555
    })
  );
  t.false(
    isExecutable({
      mode: 0o0444
    })
  );
});
