fileID = fopen('../output.txt', 'r');

%reading mode (point or disk)
%findSection(fileID, "[mode]"); 
%mode = fgets(fileID);

%reading start point and radius
findSection(fileID, "[$Start]"); 
startPoint = fscanf(fileID, "%f %f", [1, 2]);
x_start = startPoint(1,1);
y_start = startPoint(1,2);
radius = fscanf(fileID, "%f");

max_x_coord = x_start;
max_y_coord = y_start;
min_x_coord = x_start;
min_y_coord = y_start;

%drawing start point
if (radius == 0.)
plot (x_start,y_start, "marker", "o", "markersize", 5 , "markerfacecolor", "cyan");
else
plot (x_start,y_start, "marker", "o", "markersize", round(radius*72), "markerfacecolor", "cyan");
end

%reading finish point
findSection(fileID, "[$Finish]");
finPoint = fscanf(fileID, "%f %f", [1, 2]);
x_fin = finPoint(1,1);
y_fin = finPoint(1,2);

if (x_fin>max_x_coord)
  max_x_coord = x_fin;
end
if (x_fin<min_x_coord)
  min_x_coord = x_fin;
end
if (y_fin>max_y_coord)
  max_y_coord = y_fin;
end
if (y_fin<min_y_coord)
  min_y_coord = y_fin;
end


%drawing finish point
hold on
plot (x_fin,y_fin, "marker", "*", "markersize", 10);
legend("depart","fin", "Location","NorthWest");

%reading number of obstacles
findSection(fileID, "[$NumObstacles]");
n_obstacles = fscanf(fileID, "%f", 1);
n_nodes = zeros(n_obstacles,1);

%reading node coordinates of obstacles
findSection(fileID, "[$PtsObstacles]");
for i = 1:n_obstacles
  n_nodes(i) = fscanf(fileID, "%f", 1);
  obstacleCoord = (fscanf(fileID, "%f ", [2 n_nodes(i)]))';
  max_x_obstacle = max(obstacleCoord(:,1));
  max_y_obstacle = max(obstacleCoord(:,2));
  min_x_obstacle = min(obstacleCoord(:,1));
  min_y_obstacle = min(obstacleCoord(:,2));
  if (max_x_obstacle>max_x_coord)
    max_x_coord = max_x_obstacle;
  end
  if (min_x_obstacle<min_x_coord)
    min_x_coord = min_x_obstacle;
  end
  if (max_y_obstacle>max_y_coord)
    max_y_coord = max_y_obstacle;
  end
  if (min_y_obstacle<min_y_coord)
    min_y_coord = min_y_obstacle;
  end
  %drawing filled obstacle
  hold on 
  fill(obstacleCoord(:,1), obstacleCoord(:,2), i);
endfor
axis("equal"); %equal ratio x_unit-y_unit
axis([min_x_coord-1.5*radius max_x_coord+1.5*radius min_y_coord-1.5*radius max_y_coord+1.5*radius]); %axis limits

%drawing found optimal path
status_output = findSection(fileID, "[$OptPath]");
if (status_output == 0)
  pathCoord = (fscanf(fileID, "%f %f", [2, Inf]))';
  plot(pathCoord(:,1), pathCoord(:,2));
  title("Trajectoire optimale");
endif
