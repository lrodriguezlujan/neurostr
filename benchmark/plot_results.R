library(jsonlite)
library(plotly)

## SOURCE DATA DIR
benchmark_results_dir <- "./results"
benchmark_results_files <- list.files(benchmark_results_dir,all.files = T, full.names = T, pattern = "*.json");

#' convert the json output into a table
json_benchmark_to_table <- function(f){
  
  # Read object
  json <- jsonlite::fromJSON(readLines(f))  
  
  # Get filename and node count
  name <- basename(json$file)
  nodes <- json$node_count
  
  # This gets the results as a table
  benchmarks <- json$benchmark
  
  # Remove the last row - is the mock obj
  benchmarks <- benchmarks[ !is.na(benchmarks$benchmark_name), ]
  
  # Expand time - one row per measure
  expanded_benchmarks <- dplyr::bind_rows(lapply(1:nrow(benchmarks), function(i){
    return( data.frame(filename = name, nodes = nodes, benchmark_name = as.character(benchmarks$benchmark_name[i]) , 
                       experiment_name = as.character(benchmarks$experiment_name[i]), timing = benchmarks$timings[[i]],
                       stringsAsFactors = F));
    
  }))
  
  # Chars to factors
  #expanded_benchmarks <- as.data.frame(lapply(expanded_benchmarks, function(x){if(is.character(x)) return(as.factor(x)) else return(x)}))
  
  return(expanded_benchmarks);
}

# Convert all files and bind results
all_benchmarks <- dplyr::bind_rows(lapply(benchmark_results_files, json_benchmark_to_table));


# Add file extension
all_benchmarks$extension <- toupper(tools::file_ext(all_benchmarks$filename))

# Character to factors
all_benchmarks <- as.data.frame( lapply(all_benchmarks, function(x){if(is.character(x)) return(as.factor(x)) else return(x)}))

###
# Plot read time
###

# Select data to plot
d <- subset(all_benchmarks, benchmark_name == "Read", select = c(filename, timing, extension))

# Mean
d <- aggregate( timing ~ filename + extension, d, mean)

# To ms
d$timing <- d$timing/1E3

p <- plot_ly(d, x=~paste(extension,filename), y =~timing, color = ~filename, type = "bar", colors = "Set3") %>%
  layout(title = "Mean read time", xaxis = list(title = "File (Node count)"), yaxis = list(title="Time (ms)"))

plotly_POST(p, filename = "neurostr_read_benchmark")

###
# Validate
##

# Select data to plot
d <- subset(all_benchmarks, (benchmark_name == "Validation") & (filename == "VPM_1.json"), select = c(experiment_name, timing))

# Mean
d <- aggregate( timing ~ experiment_name, d, mean)


p <- plot_ly(d, x=~paste0(experiment_name), y =~timing, color = ~experiment_name, type = "bar", colors = "Set3") %>%
  layout(title = "Mean runtime - VPM_1", xaxis = list(title=""),yaxis = list(title="Time (us)", type = "log"))
plotly_POST(p, filename = "neurostr_validation_VPM1_benchmark")

###
# Measures
##

# Select data to plot
d <- subset(all_benchmarks, (benchmark_name == "Measures") & (filename == "VPM_1.json"), select = c(experiment_name, timing))

# Mean
d <- aggregate( timing ~ experiment_name, d, mean)


p <- plot_ly(d, x=~paste0(experiment_name), y =~timing, color = ~experiment_name, type = "bar", colors = "Set3") %>%
  layout(title = "Mean runtime - VPM_1", xaxis = list(title=""),yaxis = list(title="Time (us)", type = "log"))
plotly_POST(p, filename = "neurostr_measure_VPM1_benchmark")
