function compareResults( csv_file_parallel, csv_file_nonparallel )
%PLOTRESULTS Plot the rows vs cols vs time matrix from the scripts
%   Input is the path to the CSV file that was generated from the run.sh
%   script. This will plot it in 3 dimensions for your viewing pleasure.

results_p = csvread(csv_file_parallel);
results_np = csvread(csv_file_nonparallel);

%plot3(results_p(:,1), results_p(:,2), results_p(:,3), 'xb');
nonparallel = fit(results_np(:,1:2), results_np(:,3), 'cubicinterp');
plot(nonparallel);
alpha(.4);
xlabel('Number of rows');
ylabel('Number of columns');
zlabel('Time for multiplication (seconds)');
grid on;
hold on;
%plot3(results_np(:,1), results_np(:,2), results_np(:,3), 'xr');
parallel = fit(results_p(:,1:2), results_p(:,3), 'cubicinterp');
plot(parallel);
%legend('Parallel', 'Nonparallel');
legend('Nonparallel', 'Parallel');

end