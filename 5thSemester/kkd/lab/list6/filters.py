import numpy as np
from scipy.ndimage import uniform_filter

def lowpass(color_data: np.ndarray, kernel_size: int) -> np.ndarray:
    filtered = uniform_filter(color_data.astype(float), size=kernel_size, mode='nearest')
    return np.round(filtered).astype(np.uint8)

def highpass(color_data: np.ndarray, lowpass_data: np.ndarray) -> np.ndarray:
    return (color_data.astype(np.int16) - lowpass_data.astype(np.int16))