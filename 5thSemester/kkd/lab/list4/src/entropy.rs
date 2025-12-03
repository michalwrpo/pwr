use std::collections::HashMap;

pub fn calculate_entropy(data: &Vec<i16>) -> f64 {
    let mut data_scaled = Vec::new();

    for n in data {
        data_scaled.push((n + 256) % 256);
    }

    let mut result = 0.0;
    let map = probability(&data_scaled);

    for (_, prob) in map {
        result -= prob * prob.log2();
    }

    result
}

fn probability(data: &Vec<i16>) -> HashMap<i16, f64> {
    let mut counts = HashMap::new();
    let mut result = HashMap::new();

    for num in data {
        let count = counts.entry(*num).or_insert(0);
        *count += 1;
    }

    let total = data.len();


    for (k, v) in counts {
        result.insert(k, v as f64 / total as f64);
    }

    result
}