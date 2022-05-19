use std::time::{SystemTime, UNIX_EPOCH};

#[no_mangle]
pub extern "C" fn good_time() -> u128 {
    let start = SystemTime::now();
    let since_the_epoch = start
        .duration_since(UNIX_EPOCH)
        .expect("Time went backwards");

    since_the_epoch.as_nanos()
}
