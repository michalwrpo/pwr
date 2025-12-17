import numpy as np

def calculate_mse_and_snr(original_data, quantized_data):
    original_data = original_data.astype(np.float64)
    quantized_data = quantized_data.astype(np.float64)
    
    error_signal = original_data - quantized_data
    
    N_total = original_data.size 
    
    mse = np.sum(error_signal**2) / N_total
    
    signal_power = np.sum(original_data**2)
    
    noise_power = np.sum(error_signal**2)
    
    if noise_power == 0:
        snr = np.inf
    else:
        snr = 10 * np.log10(signal_power / noise_power)
        
    return mse, snr