use std::collections::{HashMap, HashSet};
use std::env::args;
use std::fs::File;
use std::io::{BufRead, BufReader, BufWriter, Write};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut args = args().skip(1);
    if let Some(infopath) = args.next() {
        let mut inp = BufReader::new(File::open(infopath)?);
        let (headers, data_map) = process_info_file(&mut inp)?;
    }

    let mut parsed_headers = vec![];
    let mut parsed_data = vec![];

    while let Some(datapath) = args.next() {
        let mut inp = BufReader::new(File::open(datapath)?);
        let (headers, data_map) = dbg!(process_data_file(&mut inp)?);
        parsed_headers.push(headers);
        parsed_data.push(data_map);
    }

    combine(parsed_headers, parsed_data);

    Ok(())
}

fn process_info_file(
    inp: &mut impl BufRead,
) -> Result<(Vec<String>, Vec<Vec<String>>), Box<dyn std::error::Error>> {
    let mut list = vec![];
    let mut lines = inp.lines().filter_map(Result::ok);
    let headers = lines.next().unwrap().split(',').map(String::from).collect();
    lines.for_each(|line| {
        let split_line = line.split(',').map(String::from).collect::<Vec<String>>();

        list.push(split_line);
    });

    Ok((headers, list))
}

fn process_data_file(
    inp: &mut impl BufRead,
) -> Result<(Vec<String>, HashMap<String, Vec<Vec<String>>>), Box<dyn std::error::Error>> {
    let mut map = HashMap::new();
    let mut lines = inp.lines().filter_map(Result::ok);
    let headers = lines.next().unwrap().split(',').map(String::from).collect();
    lines.for_each(|line| {
        let split_line = line.split(',').map(String::from).collect::<Vec<String>>();

        if map.get(&split_line[0]).is_none() {
            map.insert(split_line[0].clone(), vec![split_line]);
        } else {
            map.get_mut(&split_line[0]).unwrap().push(split_line);
        }
    });

    Ok((headers, map))
}

fn combine(headers: Vec<Vec<String>>, data: Vec<HashMap<String, Vec<Vec<String>>>>) {
    let mut header_goal = HashSet::new();

    for header_set in headers {
        for key in header_set {
            header_goal.insert(key);
        }
    }

    println!("{:?}", header_goal);
}
