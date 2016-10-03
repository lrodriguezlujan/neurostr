library(jsonlite)

benchmark_results <- "[{ 'benchmark_name' : 'swc_read', 'experiment_name' : 'swc_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A9-7.CNG.swc ], 'timings' : [ 522 ] } 
{ 'benchmark_name' : 'swc_read', 'experiment_name' : 'swc_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/cZI_2.CNG.swc ], 'timings' : [ 2290 ] } 
{ 'benchmark_name' : 'swc_read', 'experiment_name' : 'swc_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/VPM_1.CNG.swc ], 'timings' : [ 5259 ] } 
{ 'benchmark_name' : 'asc_read', 'experiment_name' : 'asc_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/02b_pyramidal1aACC.ASC ], 'timings' : [ 930 ] } 
{ 'benchmark_name' : 'asc_read', 'experiment_name' : 'asc_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/cZI_2.asc ], 'timings' : [ 3304 ] } 
{ 'benchmark_name' : 'asc_read', 'experiment_name' : 'asc_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/VPM_1.asc ], 'timings' : [ 7149 ] } 
{ 'benchmark_name' : 'dat_read', 'experiment_name' : 'dat_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A9-7.DAT ], 'timings' : [ 33 ] } 
{ 'benchmark_name' : 'dat_read', 'experiment_name' : 'dat_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/RC6-P1F6C4LVc-cs-Sh.DAT ], 'timings' : [ 381 ] } 
{ 'benchmark_name' : 'dat_read', 'experiment_name' : 'dat_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A090622.DAT ], 'timings' : [ 609 ] } 
{ 'benchmark_name' : 'json_read', 'experiment_name' : 'json_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A9-7.json ], 'timings' : [ 1106 ] } 
{ 'benchmark_name' : 'json_read', 'experiment_name' : 'json_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/cZI_2.json ], 'timings' : [ 4427 ] } 
{ 'benchmark_name' : 'json_read', 'experiment_name' : 'json_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/VPM_1.json ], 'timings' : [ 9929 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Attached to soma', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Has soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Planar reconstruction', 'time_type' : 'microseconds', 'timings' : [ 45, 23, 22, 33, 32 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Dendrite count', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Has apical', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Has axon', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Trifurcations check', 'time_type' : 'microseconds', 'timings' : [ 28, 23, 22, 21, 20 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Linear branches', 'time_type' : 'microseconds', 'timings' : [ 7, 5, 5, 4, 4 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Zero length segments', 'time_type' : 'microseconds', 'timings' : [ 20, 9, 9, 8, 8 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Non-decreasing diameter', 'time_type' : 'microseconds', 'timings' : [ 7, 7, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Segment collision', 'time_type' : 'microseconds', 'timings' : [ 7100, 6862, 7040, 6827, 7098 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Extreme angles', 'time_type' : 'microseconds', 'timings' : [ 83, 65, 63, 63, 62 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Attached to soma', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 11 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Has soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Planar reconstruction', 'time_type' : 'microseconds', 'timings' : [ 109, 67, 66, 65, 65 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Dendrite count', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Has apical', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Has axon', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Trifurcations check', 'time_type' : 'microseconds', 'timings' : [ 136, 131, 129, 129, 156 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Linear branches', 'time_type' : 'microseconds', 'timings' : [ 25, 13, 12, 12, 12 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Zero length segments', 'time_type' : 'microseconds', 'timings' : [ 111, 35, 34, 34, 34 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Non-decreasing diameter', 'time_type' : 'microseconds', 'timings' : [ 30, 29, 28, 27, 27 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Segment collision', 'time_type' : 'microseconds', 'timings' : [ 129345, 127578, 127601, 127764, 127903 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Extreme angles', 'time_type' : 'microseconds', 'timings' : [ 335, 341, 339, 331, 348 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Attached to soma', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Has soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Planar reconstruction', 'time_type' : 'microseconds', 'timings' : [ 209, 147, 141, 140, 140 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Dendrite count', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Has apical', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Has axon', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Trifurcations check', 'time_type' : 'microseconds', 'timings' : [ 240, 212, 216, 213, 209 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Linear branches', 'time_type' : 'microseconds', 'timings' : [ 36, 54, 33, 51, 33 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Zero length segments', 'time_type' : 'microseconds', 'timings' : [ 245, 87, 72, 71, 71 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Non-decreasing diameter', 'time_type' : 'microseconds', 'timings' : [ 53, 52, 52, 52, 52 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Segment collision', 'time_type' : 'microseconds', 'timings' : [ 552686, 547418, 548886, 550026, 549609 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Extreme angles', 'time_type' : 'microseconds', 'timings' : [ 750, 676, 682, 732, 639 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'soma_surface', 'time_type' : 'microseconds', 'timings' : [ 3, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_stems', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_bifs', 'time_type' : 'microseconds', 'timings' : [ 24, 4, 3, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_branch', 'time_type' : 'microseconds', 'timings' : [ 2, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_tips', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 0 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'width', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'height', 'time_type' : 'microseconds', 'timings' : [ 5, 5, 4, 5, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'depth', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'diameter', 'time_type' : 'microseconds', 'timings' : [ 8, 7, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'diameter_pow', 'time_type' : 'microseconds', 'timings' : [ 33, 27, 27, 27, 27 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'length', 'time_type' : 'microseconds', 'timings' : [ 12, 11, 10, 9, 9 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'surface', 'time_type' : 'microseconds', 'timings' : [ 13, 13, 13, 13, 13 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'section_area', 'time_type' : 'microseconds', 'timings' : [ 9, 8, 8, 8, 8 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'volume', 'time_type' : 'microseconds', 'timings' : [ 12, 11, 11, 10, 10 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'euc_distance', 'time_type' : 'microseconds', 'timings' : [ 12, 11, 11, 10, 10 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'path_distance', 'time_type' : 'microseconds', 'timings' : [ 337, 289, 288, 288, 320 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'branch_order', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 2, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'terminal_degree', 'time_type' : 'microseconds', 'timings' : [ 69, 65, 64, 63, 62 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'taper_1', 'time_type' : 'microseconds', 'timings' : [ 4, 5, 14, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'taper_2', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 2, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'branch_pathlength', 'time_type' : 'microseconds', 'timings' : [ 15, 5, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'contraction', 'time_type' : 'microseconds', 'timings' : [ 5, 5, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'fragmentation', 'time_type' : 'microseconds', 'timings' : [ 2, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'daughter_ratio', 'time_type' : 'microseconds', 'timings' : [ 7, 5, 3, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'partition_asymmetry', 'time_type' : 'microseconds', 'timings' : [ 5, 4, 3, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'rall_power', 'time_type' : 'microseconds', 'timings' : [ 38, 36, 35, 35, 35 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'pk', 'time_type' : 'microseconds', 'timings' : [ 40, 40, 39, 39, 39 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'pk_classic', 'time_type' : 'microseconds', 'timings' : [ 7, 7, 7, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'pk_2', 'time_type' : 'microseconds', 'timings' : [ 4, 4, 3, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_ampl_local', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_ampl_remote', 'time_type' : 'microseconds', 'timings' : [ 5, 4, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_tilt_local', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_tilt_remote', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_torque_local', 'time_type' : 'microseconds', 'timings' : [ 8, 7, 6, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_torque_remote', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 6, 6, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'last_parent_diam', 'time_type' : 'microseconds', 'timings' : [ 4, 3, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'hillman_threshold', 'time_type' : 'microseconds', 'timings' : [ 4, 3, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'fractal_dim', 'time_type' : 'microseconds', 'timings' : [ 314, 307, 306, 305, 305 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'soma_surface', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_stems', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_bifs', 'time_type' : 'microseconds', 'timings' : [ 8, 4, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_branch', 'time_type' : 'microseconds', 'timings' : [ 1, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_tips', 'time_type' : 'microseconds', 'timings' : [ 1, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'width', 'time_type' : 'microseconds', 'timings' : [ 21, 18, 17, 17, 17 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'height', 'time_type' : 'microseconds', 'timings' : [ 18, 17, 17, 17, 17 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'depth', 'time_type' : 'microseconds', 'timings' : [ 18, 17, 17, 17, 16 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'diameter', 'time_type' : 'microseconds', 'timings' : [ 40, 38, 37, 36, 36 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'diameter_pow', 'time_type' : 'microseconds', 'timings' : [ 137, 134, 145, 142, 152 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'length', 'time_type' : 'microseconds', 'timings' : [ 53, 50, 48, 47, 46 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'surface', 'time_type' : 'microseconds', 'timings' : [ 70, 71, 66, 65, 64 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'section_area', 'time_type' : 'microseconds', 'timings' : [ 44, 51, 40, 39, 38 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'volume', 'time_type' : 'microseconds', 'timings' : [ 59, 57, 56, 54, 54 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'euc_distance', 'time_type' : 'microseconds', 'timings' : [ 48, 47, 46, 46, 45 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'path_distance', 'time_type' : 'microseconds', 'timings' : [ 3588, 3962, 3699, 3641, 3557 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'branch_order', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'terminal_degree', 'time_type' : 'microseconds', 'timings' : [ 359, 396, 384, 365, 441 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'taper_1', 'time_type' : 'microseconds', 'timings' : [ 3, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'taper_2', 'time_type' : 'microseconds', 'timings' : [ 3, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'branch_pathlength', 'time_type' : 'microseconds', 'timings' : [ 14, 13, 12, 12, 12 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'contraction', 'time_type' : 'microseconds', 'timings' : [ 13, 13, 24, 23, 12 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'fragmentation', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'daughter_ratio', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'partition_asymmetry', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'rall_power', 'time_type' : 'microseconds', 'timings' : [ 31, 29, 28, 39, 38 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'pk', 'time_type' : 'microseconds', 'timings' : [ 31, 30, 30, 29, 29 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'pk_classic', 'time_type' : 'microseconds', 'timings' : [ 8, 7, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'pk_2', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_ampl_local', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_ampl_remote', 'time_type' : 'microseconds', 'timings' : [ 6, 6, 6, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_tilt_local', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_tilt_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_torque_local', 'time_type' : 'microseconds', 'timings' : [ 10, 8, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_torque_remote', 'time_type' : 'microseconds', 'timings' : [ 9, 8, 8, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'last_parent_diam', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'hillman_threshold', 'time_type' : 'microseconds', 'timings' : [ 4, 3, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'fractal_dim', 'time_type' : 'microseconds', 'timings' : [ 3667, 3583, 3495, 3549, 3429 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'soma_surface', 'time_type' : 'microseconds', 'timings' : [ 2, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_stems', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_bifs', 'time_type' : 'microseconds', 'timings' : [ 16, 4, 3, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_branch', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_tips', 'time_type' : 'microseconds', 'timings' : [ 1, 1, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'width', 'time_type' : 'microseconds', 'timings' : [ 20, 18, 17, 17, 16 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'height', 'time_type' : 'microseconds', 'timings' : [ 17, 17, 16, 16, 16 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'depth', 'time_type' : 'microseconds', 'timings' : [ 28, 26, 16, 16, 26 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'diameter', 'time_type' : 'microseconds', 'timings' : [ 50, 49, 37, 37, 55 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'diameter_pow', 'time_type' : 'microseconds', 'timings' : [ 137, 134, 184, 159, 157 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'length', 'time_type' : 'microseconds', 'timings' : [ 54, 50, 49, 90, 63 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'surface', 'time_type' : 'microseconds', 'timings' : [ 80, 66, 64, 64, 63 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'section_area', 'time_type' : 'microseconds', 'timings' : [ 45, 42, 40, 39, 51 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'volume', 'time_type' : 'microseconds', 'timings' : [ 89, 59, 57, 56, 55 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'euc_distance', 'time_type' : 'microseconds', 'timings' : [ 59, 47, 46, 46, 45 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'path_distance', 'time_type' : 'microseconds', 'timings' : [ 3772, 3659, 3807, 3705, 3543 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'branch_order', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'terminal_degree', 'time_type' : 'microseconds', 'timings' : [ 362, 357, 486, 354, 353 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'taper_1', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'taper_2', 'time_type' : 'microseconds', 'timings' : [ 3, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'branch_pathlength', 'time_type' : 'microseconds', 'timings' : [ 14, 13, 25, 23, 12 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'contraction', 'time_type' : 'microseconds', 'timings' : [ 13, 13, 12, 12, 12 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'fragmentation', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'daughter_ratio', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'partition_asymmetry', 'time_type' : 'microseconds', 'timings' : [ 7, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'rall_power', 'time_type' : 'microseconds', 'timings' : [ 31, 28, 39, 38, 27 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'pk', 'time_type' : 'microseconds', 'timings' : [ 30, 30, 29, 29, 29 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'pk_classic', 'time_type' : 'microseconds', 'timings' : [ 8, 7, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'pk_2', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_ampl_local', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 5, 5, 6 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_ampl_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_tilt_local', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 6, 6, 22 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_tilt_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 22, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_torque_local', 'time_type' : 'microseconds', 'timings' : [ 10, 8, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_torque_remote', 'time_type' : 'microseconds', 'timings' : [ 9, 8, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'last_parent_diam', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'hillman_threshold', 'time_type' : 'microseconds', 'timings' : [ 4, 3, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'fractal_dim', 'time_type' : 'microseconds', 'timings' : [ 3442, 3475, 3536, 3602, 3439 ] }]"

# string ""
benchmark_results <- gsub("'","\"",benchmark_results,fixed = T)
# ADd , bw benchmarks
benchmark_results <- gsub("\n",",\n",benchmark_results,fixed = F)
# Remove factors
benchmark_results <- gsub("\"factors\"[^,]*,","",benchmark_results,fixed = F, perl =T)
# Read
res <- fromJSON(benchmark_results)

extract_size <- function(s){
  if( length(grep("small",s, fixed = T)) != 0 ){
    return("small")
  } else if( length(grep("large",s, fixed = T)) != 0 ){
    return("large")
  } else if( length(grep("medium",s,fixed = T)) != 0 || length(grep("med",s,fixed = T)) != 0){
    return("medium")
  } else 
    return(NA);
}

extract_experiment <- function(s){
  if( length(grep("asc_read",s, fixed = T)) != 0 ){
    return("Read ASC")
  } else if( length(grep("swc_read",s, fixed = T)) != 0 ){
    return("Read SWC")
  } else if( length(grep("json_read",s,fixed = T)) != 0 ){
    return("Read JSON")
  } else if( length(grep("dat_read",s,fixed = T)) != 0 ){
    return("Read DAT")
  } else if( length(grep("Validation",s,fixed = T)) != 0 ){
    return("Validation")
  } else if( length(grep("Measure",s,fixed = T)) != 0 ){
    return("Measure")
  } else 
    return(NA);
}

# Extract size
neuron_size <- sapply(1:nrow(res),function(i){
  size <- extract_size(as.character(res$benchmark_name[i]))
  if(is.na(size))
    size <- extract_size(as.character(res$experiment_name[i]))
  return(size)
})

experiment_type <- sapply(res$benchmark_name,extract_experiment)

res <- cbind.data.frame(res,neuron_size = neuron_size)
res <- cbind.data.frame(res,experiment_type = experiment_type)
res <- cbind.data.frame(res,timings_mean = sapply(res$timings,mean))
res <- cbind.data.frame(res,timings_sd = sapply(res$timings,sd))


# OUTPUT
library(ggplot2)

version <- "6abd284"
basefolder <- "/home/luis/github/NeuroStr/c/utils/benchmark/Results"
basepath <- file.path(basefolder, version)

# Create dir
dir.create( basepath , showWarnings = FALSE)

# Save csv
table_csv <- res[,c(-4,-5)]
table_name <- file.path(basepath,"results.csv");
write.csv(table_csv,file = table_name,row.names = F,fileEncoding = "UTF8")

# Plot read timings
res_read <- res[res$benchmark_name %in% c("swc_read","asc_read","json_read","dat_read"),]
g<-ggplot(res_read, aes(x=neuron_size, fill = experiment_type, y=timings_mean/1E6)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("Reconstruction size") +
  ylab("Mean time (s)") 
ggsave(filename = file.path(basepath,"read.svg"),plot = g)


# Validation timings
res_validation <- res[res$experiment_type == "Validation",]
res_validation$timings_mean[res_validation$timings_mean <= 1] <- 1
g<-ggplot(res_validation, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("Reconstruction size") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"validation_all.svg"),plot = g)

#Individual
res_validation_large <- res_validation[res_validation$neuron_size == "large",]
g<-ggplot(res_validation_large, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"validation_large.svg"),plot = g)

res_validation_medium <- res_validation[res_validation$neuron_size == "medium",]
g<-ggplot(res_validation_medium, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"validation_medium.svg"),plot = g)

res_validation_small <- res_validation[res_validation$neuron_size == "small",]
g<-ggplot(res_validation_small, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"validation_small.svg"),plot = g)



# Measure timings
res_measure <- res[res$experiment_type == "Measure",]
res_measure$timings_mean[res_measure$timings_mean <= 1] <- 1
g<-ggplot(res_measure, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("Reconstruction size") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"measures_all.svg"),plot = g)

# Individual
res_measure_large <- res_measure[res_measure$neuron_size == "large",]
g<-ggplot(res_measure_large, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"measures_large.svg"),plot = g)

res_measure_medium <- res_measure[res_measure$neuron_size == "medium",]
g<-ggplot(res_measure_medium, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"measures_medium.svg"),plot = g)

res_measure_small <- res_measure[res_measure$neuron_size == "small",]
g<-ggplot(res_measure_small, aes(x=neuron_size, fill = experiment_name, y=timings_mean)) +
  geom_bar(position="dodge", stat="identity") +
  xlab("") +
  ylab("Mean time (us)") +
  scale_y_log10()
ggsave(filename = file.path(basepath,"measures_small.svg"),plot = g)