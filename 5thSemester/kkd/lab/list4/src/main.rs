use std::env;
use std::fs;
use std::process;
use std::error::Error;

use list4::calculate_predictions;

fn run(file_name: &str) -> Result<(), Box<dyn Error>> {    
    let contents = fs::read(file_name)?;

    let header_len = 18;

    if contents.len() < header_len {
        return Err("No header present inside the file".into());
    }

    let iid_len = contents[0] as usize;
    let cm_len = u16::from_ne_bytes([contents[5], contents[6]]) as usize;
    let width = u16::from_ne_bytes([contents[12], contents[13]]) as usize;
    let height = u16::from_ne_bytes([contents[14], contents[15]]) as usize;

    let img_start = header_len + iid_len + cm_len;
    let img_end = header_len + iid_len + cm_len + 3 * width * height;

    if contents.len() < img_end {
        return Err("File length shorter then specified in header".into());
    }

    calculate_predictions(width, height, &contents[img_start..img_end]);

    Ok(())
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("No file name has been given.");
        process::exit(1);
    }

    if let Err(e) = run(&args[1]) {
        eprintln!("Application error: {e}");
        process::exit(1);
    }
}