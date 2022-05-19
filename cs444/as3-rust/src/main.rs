#![feature(try_trait)]
#![allow(dead_code)]

use std::env::args;
use std::fs::{self, metadata, read_link, Metadata};
use std::io;
use std::ops::Try;
use std::os::unix::fs::MetadataExt;
use std::path::PathBuf;

fn main() {
    args().skip(1).for_each(|path| {
        if let Err(e) = stat(&PathBuf::from(&path)) {
            eprintln!("Err {}", e);
            eprintln!("Error stating {}.", &path);
        }
    })
}

fn stat(path: &PathBuf) -> io::Result<()> {
    let data: Metadata = metadata(path)?;
    println!(
        "File: {}",
        path.file_name()
            .map(|os_str: &std::ffi::OsStr| { os_str.to_str() })
            .into_result()
            .map_err(|_| { io::Error::from(io::ErrorKind::NotFound) })?
            .unwrap_or("Corrupted file name.")
    );

    print!("  Filetype:                 ");
    match data.file_type() {
        typ if typ.is_dir() => println!("directory"),
        typ if typ.is_symlink() => {
            print!("Symbolic link");
            match read_link(path) {
                Ok(path) => println!(
                    " -> {}",
                    path.file_name()
                        .map(|os_str: &std::ffi::OsStr| os_str.to_str())
                        .into_result()
                        .map_err(|_| io::Error::from(io::ErrorKind::NotFound))?
                        .unwrap_or("Corrupted file name.")
                ),
                Err(e) if e.kind() == io::ErrorKind::NotFound => {
                    println!(" - with dangling destination");
                }
                _ => {
                    eprintln!("Error accessing link filename.");
                }
            }
        }
        typ if typ.is_file() => println!("regular file"),
        _ => println!("unknown file type"),
    }
    println!("Device ID Number: {:11}", data.rdev());
    println!("Inode Number: {:11}", data.ino());
    println!("Mode: {:11}", data.mode());

    Ok(())
}

fn stringified_mode(mode: u32) -> String {
    let mut build = String::with_capacity(10);
}
