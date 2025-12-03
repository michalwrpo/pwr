mod entropy;

use std::cmp;

pub fn calculate_predictions(
    width: usize, 
    height: usize, 
    image: &[u8]
) {
    let mut image_vector = Vec::new();

    for byte in image {
        image_vector.push(*byte as i16);
    }

    let original_entropy = entropy::calculate_entropy(&image_vector);
    println!("Original image entropy: {}", original_entropy);

    let size = width * height;
    let mut red = Vec::new();
    let mut green = Vec::new();
    let mut blue = Vec::new();

    let mut red_v = Vec::new();
    let mut green_v = Vec::new();
    let mut blue_v = Vec::new();
    

    for i in 0..size {
        blue.push(image[3 * i]);
        green.push(image[3 * i + 1]);
        red.push(image[3 * i + 2]);

        blue_v.push(image[3 * i] as i16);
        green_v.push(image[3 * i + 1] as i16);
        red_v.push(image[3 * i + 2] as i16);
    }

    let blue_entropy = entropy::calculate_entropy(&blue_v);
    println!("Blue entropy: {}", blue_entropy);

    let green_entropy = entropy::calculate_entropy(&green_v);
    println!("Green entropy: {}", green_entropy);

    let red_entropy = entropy::calculate_entropy(&red_v);
    println!("Red entropy: {}", red_entropy);


    let (best, bestarg) = best_prediction(3 * width, height, image, 3);
    println!("\nBest prediction: {bestarg}\nEntropy: {best}");
    
    let (best_b, b_arg) = best_prediction(width, height, &blue, 1);   
    println!("\nBlue best prediction: {b_arg}\nEntropy: {best_b}");

    let (best_g, g_arg) = best_prediction(width, height, &green, 1);   
    println!("\nGreen best prediction: {g_arg}\nEntropy: {best_g}");

    let (best_r, r_arg) = best_prediction(width, height, &red, 1);   
    println!("\nRed best prediction: {r_arg}\nEntropy: {best_r}");
}

pub fn best_prediction(
    width: usize,
    height: usize,
    image: &[u8],
    step: usize
) -> (f64, usize) {
    let result1 = prediction_n(width, height, image);
    let result2 = prediction_w(width, height, image, step);
    let result3 = prediction_nw(width, height, image, step);
    let result4 = prediction4(width, height, image, step);
    let result5 = prediction5(width, height, image, step);
    let result6 = prediction6(width, height, image, step);
    let result7 = prediction7(width, height, image, step);
    let result8 = prediction_new(width, height, image, step);
    
    let mut entropy: [f64; 8] = [0.0; 8];
    
    entropy[0] = entropy::calculate_entropy(&result1);
    entropy[1] = entropy::calculate_entropy(&result2);
    entropy[2] = entropy::calculate_entropy(&result3);
    entropy[3] = entropy::calculate_entropy(&result4);
    entropy[4] = entropy::calculate_entropy(&result5);
    entropy[5] = entropy::calculate_entropy(&result6);
    entropy[6] = entropy::calculate_entropy(&result7);
    entropy[7] = entropy::calculate_entropy(&result8);

    // println!("(step={step}) {}", entropy[7]);

    let mut min = entropy[0];
    let mut minarg = 1;

    for i in 0..8 {
        // println!("{} {}", i + 1, entropy[i]);
        if entropy[i] < min {
            min = entropy[i];
            minarg = i + 1;
        }
    }

    (min, minarg)
}

pub fn prediction_n(
    width: usize, 
    height: usize, 
    image: &[u8],
) -> Vec<i16> {
    let mut result = Vec::new();
    
    for i in 0..width*height {
        let x = image[i] as i16;
        let mut n = 0;

        if i >= width {
            n = image[i - width] as i16;
        }

        result.push(x - n);
    }

    result
}

pub fn prediction_w(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;
        let mut w = 0;

        if i % width >= step {
            w = image[i - step] as i16;
        }

        result.push(x - w);
    }

    result
}

pub fn prediction_nw(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;
        let mut nw = 0;

        if i >= width && i % width >= step {
            nw = image[i - width - step] as i16;
        }

        result.push(x - nw);
    }

    result
}

pub fn prediction4(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;
        let mut n = 0;
        let mut w = 0;
        let mut nw = 0;

        if i >= width {
            n = image[i - width] as i16;
        }

        if i % width >= step {
            w = image[i - step] as i16;
        }

        if i >= width && i % width >= step {
            nw = image[i - width - step] as i16;
        }

        result.push(x - (n + w - nw));
    }

    result
}

pub fn prediction5(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;
        let mut n = 0;
        let mut w = 0;
        let mut nw = 0;

        if i >= width {
            n = image[i - width] as i16;
        }

        if i % width >= step {
            w = image[i - step] as i16;
        }

        if i >= width && i % width >= step {
            nw = image[i - width - step] as i16;
        }

        result.push(x - (n + (w - nw) / 2));
    }

    result
}

pub fn prediction6(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;
        let mut n = 0;
        let mut w = 0;
        let mut nw = 0;

        if i >= width {
            n = image[i - width] as i16;
        }

        if i % width >= step {
            w = image[i - step] as i16;
        }

        if i >= width && i % width >= step {
            nw = image[i - width - step] as i16;
        }

        result.push(x - (w + (n - nw) / 2));
    }

    result
}

pub fn prediction7(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;
        let mut n = 0;
        let mut w = 0;

        if i >= width {
            n = image[i - width] as i16;
        }

        if i % width >= step {
            w = image[i - step] as i16;
        }

        result.push(x - (n + w) / 2);
    }

    result
}

pub fn prediction_new(
    width: usize, 
    height: usize, 
    image: &[u8],
    step: usize
) -> Vec<i16> {
    let mut result = Vec::new();

    for i in 0..width*height {
        let x = image[i] as i16;

        if i < width || i % width < step {
            result.push(x);
        } else {
            let n = image[i - step] as i16;
            let w = image[i - width] as i16;
            let nw = image[i - width - step] as i16;

            if nw >= cmp::max(n, w) {
                result.push(x - cmp::max(n, w));
            } else if nw <= cmp::min(n, w) {
                result.push(x - cmp::min(n, w));
            } else {
                result.push(x - (n + w - nw));
            }
        }
    }

    result
}