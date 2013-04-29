function plotResults( csv_file )
%PLOTRESULTS Plot the rows vs cols vs time matrix from the scripts
%   Input is the path to the CSV file that was generated from the run.sh
%   script. This will plot it in 3 dimensions for your viewing pleasure.

results = csvread(csv_file);

%plot3(results(:,1), results(:,2), results(:,3));
%xlabel('rows')
%ylabel('cols')
%zlabel('t')
%grid on
%axis square

cline(results(:,1), results(:,2), results(:,3));
view(3);
xlabel('Number of rows');
ylabel('Number of columns');
zlabel('Time for multiplication (minutes)');
colorbar;

end