import matplotlib.pyplot as plt
import numpy as np

# Define the eta range and bin edges
def main():
    ppbins = np.array([
        -5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, 
        -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, 
        -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, 
        -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, 
        -0.435, -0.348, -0.261, -0.174, -0.087, 
        +0.000, 
        +0.087, +0.174, +0.261, +0.348, +0.435, +0.522, +0.609, +0.696, +0.783, 
        +0.879, +0.957, +1.044, +1.131, +1.218, +1.305, +1.392, +1.479, +1.566, 
        +1.653, +1.740, +1.830, +1.930, +2.043, +2.172, +2.322, +2.500, +2.650, 
        +2.853, +2.964, +3.139, +3.314, +3.489, +3.664, +3.839, +4.013, +4.191, 
        +4.363, +4.538, +4.716, +4.889, +5.191
        ])  


    upcbins = np.array([
        -5.191, -4.013, -2.964, 
        -2.500, -1.740, -1.305, -1.044, -0.696, -0.435, -0.174,
        +0.000, 
        +0.174, +0.435, +0.696, +1.044, +1.305, +1.740, +2.500, 
        +2.964, +4.013, +5.191
        ])

    detector_edges = np.array([
        -5.191, -2.964, -2.500, -1.305,
        +1.305, +2.500, +2.964, +5.191
        ])

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 4))
    for x in ppbins:
        ax1.axvline(x, color='gray', linestyle='-', alpha=0.5)
    ax1.set_xlabel('$\\eta$')
    ax1.set_title('Default binning')
    ax1.yaxis.set_visible(False)

    for x in upcbins:
        ax2.axvline(x, color='gray', linestyle='-', alpha=0.5)
    ax2.set_xlabel('$\\eta$')
    ax2.set_title('Working binning')
    ax2.yaxis.set_visible(False)

    for x in detector_edges:
        ax1.axvline(x, color='black', linestyle=':', alpha=1)
        ax2.axvline(x, color='black', linestyle=':', alpha=1)
    plt.savefig("eta_bins.png")

if __name__ == "__main__":
    main()


