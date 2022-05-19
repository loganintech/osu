#![allow(unused)]
use std::collections::hash_map::DefaultHasher;
use std::ffi::{CString, CStr};
use std::fs::File;
use std::hash::{Hash, Hasher};
use std::io::{BufRead, BufReader, Write};
use std::env::args;

#[repr(C)]
#[derive(Debug, Clone)]
pub struct Employee {
    id: CString,         // exactly 8 bytes
    name: CString,       // at most 200 bytes
    bio: CString,        // at most 500 bytes
    manager_id: CString, // exactly 8 bytes
}

impl Employee {
    fn from_id(id: &str) -> Self {
        Self {
            id: CString::new(id.as_bytes()).expect("An invalid id was passed to Employee"),
            name: CString::default(),
            bio: CString::default(),
            manager_id: CString::default(),
        }
    }
}

fn main() -> std::result::Result<(), Box<dyn std::error::Error>> {
    let mut args = args().skip(1);
    let control_arg = args.next();
    match control_arg.as_ref().map(|s| s.as_str()) {
        Some("C")  => {
            println!("Loading from CSV and creating the index.\nPlease check for EmployeeIndex file in the current directory.");

            let employees = read_csv("Employee.csv")?;

            let mut map = EmployeeMap::new();
            for emp in employees {
                map.insert(emp);
            }

            write_index("./EmployeeIndex", map)?;
        },
        Some("L") => {
            let employee_map = read_index("./EmployeeIndex");
            if employee_map.is_err() {
                let employees = read_csv("./Employee.csv")?;

                let mut map = EmployeeMap::new();
                for emp in employees {
                    map.insert(emp);
                }

                write_index("./EmployeeIndex", map)?;
            }

            if let Ok(employee_map) = read_index("./EmployeeIndex") {
                match args.next() {
                    Some(id) => {
                        if let Some(emp) = employee_map.lookup(&id) {
                            println!("Found Employee:\n{:#?}", emp);
                        } else {
                            eprintln!("Couldn't find employee with that ID.");
                        }
                    },
                    None => {
                        eprintln!("You must include an item ID to lookup. Usage: eindex L [id]");
                    }
                }
            } else {
                println!("Error reading from index, was it corrupted?");
            }
        },
        _ => {
            println!("Usage:");
            println!("\teindex C \tRead the input CSV and create the index file.");
            println!("\teindex L [id] \tRead the index file and lookup a record. Will create the index file if it doesn't exist.");
        }
    }

    Ok(())
}

impl Hash for Employee {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

fn calc_hash<T: Hash>(t: &T) -> u64 {
    let mut s = DefaultHasher::new();
    t.hash(&mut s);
    s.finish()
}

#[derive(Debug)]
struct EmployeeMap {
    map: Vec<Vec<Employee>>,
    buckets: usize,
}

impl EmployeeMap {
    fn new() -> Self {
        Self {
            map: vec![vec![]; 1],
            buckets: 1,
        }
    }

    fn insert(&mut self, item: Employee) {
        let hash = calc_hash(&item);
        let bucket_idx = hash as usize % self.buckets;
        if self.map[bucket_idx].len() < 4 {
            self.map[bucket_idx].push(item);
        } else {
            self.grow_and_insert(item);
        }
    }

    fn grow_and_insert(&mut self, item: Employee) {
        let mut employees: Vec<Employee> = Vec::new();
        for bucket in self.map.iter().cloned() {
            for emp in bucket {
                employees.push(emp);
            }
        }

        employees.push(item);

        self.buckets += 1;
        let mut new_map: Vec<Vec<Employee>> = vec![vec![]; self.buckets];

        for employee in employees {
            let hash = calc_hash(&employee);
            let bucket_idx = hash as usize % self.buckets;
            if new_map[bucket_idx].len() < 4 {
                new_map[bucket_idx].push(employee);
            }
        }

        self.map = new_map;
    }

    fn into_tuple_list(self) -> Vec<(usize, Employee)> {
        let mut list: Vec<(usize, Employee)> = vec![];
        for (idx, bucket) in self.map.into_iter().enumerate() {
            for emp in bucket {
                list.push((idx, emp));
            }
        }
        list
    }

    fn from_tuple_list(list: Vec<(usize, Employee)>) -> Self {
        let mut max_bucket_size = 0;
        for item in &list {
            if item.0 > max_bucket_size {
                max_bucket_size = item.0;
            }
        }

        // We record bucket indicies in the file so the size is 1 + the max index
        max_bucket_size += 1;

        let mut map: Vec<Vec<Employee>> = vec![vec![]; max_bucket_size];
        for item in list {
            map[item.0].push(item.1);
        }

        EmployeeMap {
            map,
            buckets: max_bucket_size,
        }
    }

    fn lookup(&self, id: &str) -> Option<Employee> {
        let hash = calc_hash(&Employee::from_id(id));
        let bucket_idx = hash as usize % self.buckets;
        for item in &self.map[bucket_idx] {
            if item.id.to_str().unwrap() == id {
                return Some(item.clone());
            }
        }

        None
    }
}

fn read_index(filepath: &str) -> Result<EmployeeMap, std::io::Error> {
    let tuples = BufReader::new(File::open(filepath)?)
        .lines()
        .filter_map(Result::ok)
        .map(|line| {
            let mut tuple_parts = line.split("|");
            let bucket_idx = tuple_parts
                .next()
                .expect("Unknown format found in index file, please recreate.");
            let bucket_idx = bucket_idx
                .parse::<usize>()
                .expect("Unknown format found in index file, please recreate.");
            let employee = tuple_parts
                .next()
                .expect("Unknown format found in index file, please recreate.");
            let employee = parse_employee(employee)
                .expect("Unknown format found in index file, please recreate.");
            (bucket_idx, employee)
        })
        .collect::<Vec<_>>();

    Ok(EmployeeMap::from_tuple_list(tuples))
}

fn write_index(filepath: &str, map: EmployeeMap) -> Result<(), std::io::Error> {
    let mut file = File::create(filepath)?;
    let tuples = map.into_tuple_list();
    for (bucket, employee) in tuples {
        file.write(format!("{}|", bucket).as_bytes())?;
        file.write(employee.id.as_bytes())?;
        file.write(b",");
        file.write(employee.name.as_bytes())?;
        file.write(b",");
        file.write(employee.bio.as_bytes())?;
        file.write(b",");
        file.write(employee.manager_id.as_bytes())?;
        file.write(b"\n");
    }

    Ok(())
}

fn parse_employee(line: &str) -> Option<Employee> {
    let mut parts = line
        .split(",")
        .filter_map(|part| CString::new(part).ok())
        .collect::<Vec<CString>>();

    if parts[0].as_bytes().len() != 8
        || parts[3].as_bytes().len() != 8
        || parts[1].as_bytes().len() > 200
        || parts[2].as_bytes().len() > 500
    {
        println!("Invalid lengths for employee {:?}", parts);
        return None;
    }

    Some(Employee {
        id: parts[0].clone(),
        name: parts[1].clone(),
        bio: parts[2].clone(),
        manager_id: parts[3].clone(),
    })
}

fn read_csv(filepath: &str) -> Result<Vec<Employee>, std::io::Error> {
    let employees = BufReader::new(File::open(filepath)?)
        .lines()
        .filter_map(Result::ok)
        .filter(|line| line.len() > 0)
        .filter_map(|line| parse_employee(&line))
        .collect::<Vec<_>>();

    Ok(employees)
}
