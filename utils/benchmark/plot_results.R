library(jsonlite)

benchmark_results <- "[{ 'benchmark_name' : 'swc_read', 'experiment_name' : 'swc_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A9-7.CNG.swc ], 'timings' : [ 550 ] } 
{ 'benchmark_name' : 'swc_read', 'experiment_name' : 'swc_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/cZI_2.CNG.swc ], 'timings' : [ 2502 ] } 
{ 'benchmark_name' : 'swc_read', 'experiment_name' : 'swc_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/VPM_1.CNG.swc ], 'timings' : [ 6811 ] } 
{ 'benchmark_name' : 'asc_read', 'experiment_name' : 'asc_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/02b_pyramidal1aACC.ASC ], 'timings' : [ 1240 ] } 
{ 'benchmark_name' : 'asc_read', 'experiment_name' : 'asc_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/cZI_2.asc ], 'timings' : [ 4190 ] } 
{ 'benchmark_name' : 'asc_read', 'experiment_name' : 'asc_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/VPM_1.asc ], 'timings' : [ 9665 ] } 
{ 'benchmark_name' : 'dat_read', 'experiment_name' : 'dat_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A9-7.DAT ], 'timings' : [ 54 ] } 
{ 'benchmark_name' : 'dat_read', 'experiment_name' : 'dat_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/RC6-P1F6C4LVc-cs-Sh.DAT ], 'timings' : [ 442 ] } 
{ 'benchmark_name' : 'dat_read', 'experiment_name' : 'dat_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A090622.DAT ], 'timings' : [ 1249 ] } 
{ 'benchmark_name' : 'json_read', 'experiment_name' : 'json_read_small', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/A9-7.json ], 'timings' : [ 1426 ] } 
{ 'benchmark_name' : 'json_read', 'experiment_name' : 'json_read_medium', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/cZI_2.json ], 'timings' : [ 5950 ] } 
{ 'benchmark_name' : 'json_read', 'experiment_name' : 'json_read_large', 'time_type' : 'microseconds', 'factor_name' : 'file', 'factors' : [ ../data/VPM_1.json ], 'timings' : [ 12048 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Attached to soma', 'time_type' : 'microseconds', 'timings' : [ 2, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Has soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Planar reconstruction', 'time_type' : 'microseconds', 'timings' : [ 91, 32, 26, 35, 34 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Dendrite count', 'time_type' : 'microseconds', 'timings' : [ 2, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Has apical', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Has axon', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Trifurcations check', 'time_type' : 'microseconds', 'timings' : [ 31, 24, 22, 20, 27 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Linear branches', 'time_type' : 'microseconds', 'timings' : [ 18, 10, 7, 5, 4 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Zero length segments', 'time_type' : 'microseconds', 'timings' : [ 20, 9, 8, 8, 8 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Non-decreasing diameter', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Segment collision', 'time_type' : 'microseconds', 'timings' : [ 1037, 1135, 1150, 947, 1031 ] } 
{ 'benchmark_name' : 'Validation - small size neuron', 'experiment_name' : 'Extreme angles', 'time_type' : 'microseconds', 'timings' : [ 91, 69, 67, 66, 66 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Attached to soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Has soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Planar reconstruction', 'time_type' : 'microseconds', 'timings' : [ 139, 85, 75, 72, 71 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Dendrite count', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Has apical', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Has axon', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Trifurcations check', 'time_type' : 'microseconds', 'timings' : [ 147, 135, 131, 131, 128 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Linear branches', 'time_type' : 'microseconds', 'timings' : [ 20, 15, 25, 29, 13 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Zero length segments', 'time_type' : 'microseconds', 'timings' : [ 139, 33, 32, 32, 33 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Non-decreasing diameter', 'time_type' : 'microseconds', 'timings' : [ 29, 59, 27, 25, 26 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Segment collision', 'time_type' : 'microseconds', 'timings' : [ 6475, 7069, 6822, 7385, 6783 ] } 
{ 'benchmark_name' : 'Validation - med size neuron', 'experiment_name' : 'Extreme angles', 'time_type' : 'microseconds', 'timings' : [ 365, 351, 349, 379, 368 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Attached to soma', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Has soma', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Planar reconstruction', 'time_type' : 'microseconds', 'timings' : [ 223, 168, 160, 153, 150 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Dendrite count', 'time_type' : 'microseconds', 'timings' : [ 2, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Has apical', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Has axon', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Trifurcations check', 'time_type' : 'microseconds', 'timings' : [ 236, 215, 217, 221, 217 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Linear branches', 'time_type' : 'microseconds', 'timings' : [ 44, 39, 37, 36, 47 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Zero length segments', 'time_type' : 'microseconds', 'timings' : [ 185, 71, 69, 67, 66 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Non-decreasing diameter', 'time_type' : 'microseconds', 'timings' : [ 52, 52, 50, 50, 64 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Segment collision', 'time_type' : 'microseconds', 'timings' : [ 40122, 38012, 38761, 36962, 36067 ] } 
{ 'benchmark_name' : 'Validation - large size neuron', 'experiment_name' : 'Extreme angles', 'time_type' : 'microseconds', 'timings' : [ 713, 702, 690, 692, 677 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'soma_surface', 'time_type' : 'microseconds', 'timings' : [ 17, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_stems', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_bifs', 'time_type' : 'microseconds', 'timings' : [ 13, 5, 3, 4, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_branch', 'time_type' : 'microseconds', 'timings' : [ 3, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'n_tips', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 0 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'width', 'time_type' : 'microseconds', 'timings' : [ 11, 9, 8, 6, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'height', 'time_type' : 'microseconds', 'timings' : [ 6, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'depth', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'diameter', 'time_type' : 'microseconds', 'timings' : [ 8, 8, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'diameter_pow', 'time_type' : 'microseconds', 'timings' : [ 35, 28, 27, 27, 27 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'length', 'time_type' : 'microseconds', 'timings' : [ 13, 11, 10, 10, 9 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'surface', 'time_type' : 'microseconds', 'timings' : [ 13, 13, 13, 13, 13 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'section_area', 'time_type' : 'microseconds', 'timings' : [ 9, 8, 8, 8, 7 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'volume', 'time_type' : 'microseconds', 'timings' : [ 12, 11, 11, 10, 10 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'euc_distance', 'time_type' : 'microseconds', 'timings' : [ 11, 10, 10, 22, 24 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'path_distance', 'time_type' : 'microseconds', 'timings' : [ 344, 462, 343, 365, 383 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'branch_order', 'time_type' : 'microseconds', 'timings' : [ 6, 3, 2, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'terminal_degree', 'time_type' : 'microseconds', 'timings' : [ 96, 87, 71, 82, 97 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'taper_1', 'time_type' : 'microseconds', 'timings' : [ 16, 2, 3, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'taper_2', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 2, 2, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'branch_pathlength', 'time_type' : 'microseconds', 'timings' : [ 11, 6, 5, 5, 14 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'contraction', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'fragmentation', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'daughter_ratio', 'time_type' : 'microseconds', 'timings' : [ 8, 5, 4, 16, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'partition_asymmetry', 'time_type' : 'microseconds', 'timings' : [ 6, 4, 4, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'rall_power', 'time_type' : 'microseconds', 'timings' : [ 71, 67, 35, 36, 35 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'pk', 'time_type' : 'microseconds', 'timings' : [ 40, 39, 40, 39, 39 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'pk_classic', 'time_type' : 'microseconds', 'timings' : [ 7, 7, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'pk_2', 'time_type' : 'microseconds', 'timings' : [ 4, 4, 4, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_ampl_local', 'time_type' : 'microseconds', 'timings' : [ 8, 5, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_ampl_remote', 'time_type' : 'microseconds', 'timings' : [ 5, 4, 4, 4, 4 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_tilt_local', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_tilt_remote', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_torque_local', 'time_type' : 'microseconds', 'timings' : [ 9, 7, 6, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'bif_torque_remote', 'time_type' : 'microseconds', 'timings' : [ 8, 7, 6, 6, 5 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'last_parent_diam', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'hillman_threshold', 'time_type' : 'microseconds', 'timings' : [ 4, 3, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - small size neuron', 'experiment_name' : 'fractal_dim', 'time_type' : 'microseconds', 'timings' : [ 432, 330, 363, 329, 322 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'soma_surface', 'time_type' : 'microseconds', 'timings' : [ 1, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_stems', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_bifs', 'time_type' : 'microseconds', 'timings' : [ 12, 7, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_branch', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'n_tips', 'time_type' : 'microseconds', 'timings' : [ 1, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'width', 'time_type' : 'microseconds', 'timings' : [ 29, 24, 21, 32, 22 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'height', 'time_type' : 'microseconds', 'timings' : [ 21, 21, 20, 20, 18 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'depth', 'time_type' : 'microseconds', 'timings' : [ 19, 18, 19, 18, 18 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'diameter', 'time_type' : 'microseconds', 'timings' : [ 42, 40, 39, 38, 37 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'diameter_pow', 'time_type' : 'microseconds', 'timings' : [ 145, 145, 143, 143, 149 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'length', 'time_type' : 'microseconds', 'timings' : [ 56, 52, 50, 48, 47 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'surface', 'time_type' : 'microseconds', 'timings' : [ 83, 67, 66, 64, 63 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'section_area', 'time_type' : 'microseconds', 'timings' : [ 45, 42, 41, 40, 39 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'volume', 'time_type' : 'microseconds', 'timings' : [ 61, 60, 60, 67, 56 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'euc_distance', 'time_type' : 'microseconds', 'timings' : [ 46, 44, 44, 60, 56 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'path_distance', 'time_type' : 'microseconds', 'timings' : [ 4233, 4053, 3626, 3561, 3848 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'branch_order', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 12, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'terminal_degree', 'time_type' : 'microseconds', 'timings' : [ 434, 382, 424, 381, 381 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'taper_1', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'taper_2', 'time_type' : 'microseconds', 'timings' : [ 3, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'branch_pathlength', 'time_type' : 'microseconds', 'timings' : [ 17, 14, 13, 13, 13 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'contraction', 'time_type' : 'microseconds', 'timings' : [ 26, 14, 34, 13, 13 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'fragmentation', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'daughter_ratio', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'partition_asymmetry', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'rall_power', 'time_type' : 'microseconds', 'timings' : [ 33, 30, 28, 28, 27 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'pk', 'time_type' : 'microseconds', 'timings' : [ 32, 32, 31, 30, 31 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'pk_classic', 'time_type' : 'microseconds', 'timings' : [ 8, 8, 8, 8, 8 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'pk_2', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_ampl_local', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_ampl_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 5, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_tilt_local', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_tilt_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_torque_local', 'time_type' : 'microseconds', 'timings' : [ 11, 9, 8, 8, 8 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'bif_torque_remote', 'time_type' : 'microseconds', 'timings' : [ 9, 20, 8, 8, 18 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'last_parent_diam', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'hillman_threshold', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - medium size neuron', 'experiment_name' : 'fractal_dim', 'time_type' : 'microseconds', 'timings' : [ 3638, 4317, 3919, 3853, 3601 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'soma_surface', 'time_type' : 'microseconds', 'timings' : [ 2, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_stems', 'time_type' : 'microseconds', 'timings' : [ 0, 0, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_bifs', 'time_type' : 'microseconds', 'timings' : [ 9, 5, 4, 3, 3 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_branch', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'n_tips', 'time_type' : 'microseconds', 'timings' : [ 1, 1, 0, 0, 0 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'width', 'time_type' : 'microseconds', 'timings' : [ 26, 20, 18, 18, 17 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'height', 'time_type' : 'microseconds', 'timings' : [ 18, 17, 17, 17, 16 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'depth', 'time_type' : 'microseconds', 'timings' : [ 18, 17, 16, 16, 16 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'diameter', 'time_type' : 'microseconds', 'timings' : [ 39, 41, 41, 40, 40 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'diameter_pow', 'time_type' : 'microseconds', 'timings' : [ 152, 145, 144, 137, 148 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'length', 'time_type' : 'microseconds', 'timings' : [ 55, 51, 49, 47, 46 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'surface', 'time_type' : 'microseconds', 'timings' : [ 71, 78, 81, 80, 66 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'section_area', 'time_type' : 'microseconds', 'timings' : [ 46, 43, 41, 40, 41 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'volume', 'time_type' : 'microseconds', 'timings' : [ 63, 60, 59, 57, 58 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'euc_distance', 'time_type' : 'microseconds', 'timings' : [ 48, 45, 54, 43, 43 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'path_distance', 'time_type' : 'microseconds', 'timings' : [ 3551, 3694, 3838, 3909, 3480 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'branch_order', 'time_type' : 'microseconds', 'timings' : [ 3, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'terminal_degree', 'time_type' : 'microseconds', 'timings' : [ 382, 381, 375, 479, 374 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'taper_1', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'taper_2', 'time_type' : 'microseconds', 'timings' : [ 3, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'branch_pathlength', 'time_type' : 'microseconds', 'timings' : [ 16, 13, 13, 12, 12 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'contraction', 'time_type' : 'microseconds', 'timings' : [ 13, 13, 13, 12, 12 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'fragmentation', 'time_type' : 'microseconds', 'timings' : [ 2, 1, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'daughter_ratio', 'time_type' : 'microseconds', 'timings' : [ 8, 6, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'partition_asymmetry', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 5, 5, 5 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'rall_power', 'time_type' : 'microseconds', 'timings' : [ 31, 28, 27, 27, 27 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'pk', 'time_type' : 'microseconds', 'timings' : [ 31, 30, 31, 31, 31 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'pk_classic', 'time_type' : 'microseconds', 'timings' : [ 8, 8, 9, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'pk_2', 'time_type' : 'microseconds', 'timings' : [ 6, 5, 6, 5, 6 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_ampl_local', 'time_type' : 'microseconds', 'timings' : [ 9, 6, 5, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_ampl_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 7, 6, 6, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_tilt_local', 'time_type' : 'microseconds', 'timings' : [ 9, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_tilt_remote', 'time_type' : 'microseconds', 'timings' : [ 7, 6, 6, 6, 6 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_torque_local', 'time_type' : 'microseconds', 'timings' : [ 11, 8, 8, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'bif_torque_remote', 'time_type' : 'microseconds', 'timings' : [ 9, 8, 7, 7, 7 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'last_parent_diam', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 1, 1, 1 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'hillman_threshold', 'time_type' : 'microseconds', 'timings' : [ 4, 2, 2, 2, 2 ] } 
{ 'benchmark_name' : 'Measure - large size neuron', 'experiment_name' : 'fractal_dim', 'time_type' : 'microseconds', 'timings' : [ 3694, 3805, 3771, 4275, 3756 ] }]"

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

version <- "f940432"
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