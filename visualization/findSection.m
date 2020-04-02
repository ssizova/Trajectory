function[status] = findSection(fid, s)
status = 0;
do 
currentLine = fgets(fid);
if (feof(fid) == 1)
  status = -1;
  break;
endif
until (!isempty(strfind(currentLine, s)))

if (status == -1)
  fprintf("Section %s is not found \n", s);
endif


