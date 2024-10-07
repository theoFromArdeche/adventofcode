program main
  implicit none
  character(200) :: line, fullPath
  character(len=:), allocatable :: dirName, searchName, path(:), indexToDir(:)
  integer, allocatable :: flag_ls(:) 
  integer, allocatable :: dirSizes(:)
  integer :: fileSize, ios, indexSearchDir, indexCurDir, indexLastDir, indexPath, i, solutionPart1, solutionPart2, targetSizePart2

  indexLastDir = 0
  indexPath = 0
  indexSearchDir = 0
  indexCurDir = 0
  fullPath = ''
  allocate(character(len=100) :: path(1000))
  allocate(character(len=100) :: indexToDir(1000))
  allocate(integer :: dirSizes(1000))
  allocate(character(len=100) :: dirName)
  allocate(character(len=100) :: searchName)
  allocate(integer :: flag_ls(1000))


  open(1, file = 'input.txt', status = 'old')

  do
    read(1, '(A)', iostat=ios) line
    if (ios /= 0) then
      if (indexPath == 1) then
        exit
      else
        line = "$ cd .."
      end if
    end if
    !print *, line

    if (len_trim(line) == 0) cycle


    if (index(line, '$ cd ') == 1) then
      call extractDirName(line, dirName)
      
      if (dirName == "..") then
        if (indexPath == 1) then
          cycle
        end if
        fullPath = fullPath(1:len_trim(fullPath)-len_trim(path(indexPath))-1)
        searchName = fullPath
        indexPath = indexPath-1
      else
        indexPath = 1+indexPath
        path(indexPath) = dirName
        searchName = trim(fullPath) // '/' // trim(dirName)
      end if

      call search(indexToDir, searchName, indexSearchDir, indexLastDir)
      if (indexSearchDir == -1) then
        indexLastDir = 1+indexLastDir
        indexCurDir = indexLastDir
        fullPath = trim(fullPath) // '/' // trim(dirName)
        indexToDir(indexCurDir) = fullPath
        dirSizes(indexCurDir) = 0
        flag_ls(indexCurDir) = 0
      else
        if (dirName == "..") then
          dirSizes(indexSearchDir) = dirSizes(indexSearchDir) + dirSizes(indexCurDir)
        end if
        indexCurDir = indexSearchDir
      end if
    
    elseif (index(line, '$ ls') == 1) then
      flag_ls(indexCurDir) = flag_ls(indexCurDir) + 1

    elseif (index(line, 'dir') /= 1 .and. flag_ls(indexCurDir) == 1) then
      call extractFileSize(line, fileSize)
      dirSizes(indexCurDir) = dirSizes(indexCurDir) + fileSize 
    !else
      !print *, 'Other line: ', trim(line)
    end if
  end do


  solutionPart1 = 0
  targetSizePart2 = 30000000 - 70000000 + dirSizes(1)
  solutionPart2 = dirSizes(1)
  do i = 1, indexLastDir
    !print *, dirSizes(i), indexToDir(i) 
    if (dirSizes(i) >= targetSizePart2 .and. dirSizes(i) < solutionPart2) then 
      solutionPart2 = dirSizes(i)
    end if
    if (dirSizes(i) <= 100000) then
      solutionPart1 = solutionPart1 + dirSizes(i)
    end if
  end do
  print *, "Part 1 solution: ", solutionPart1
  print *, "Part 2 solution: ", solutionPart2
  close(1)


contains

  subroutine extractDirName(line, dirName)
    character(len=*), intent(in) :: line
    character(len=*), intent(out) :: dirName
    integer :: start

    start = 1 + len('$ cd ')
    dirName = trim(adjustl(line(start:)))
  end subroutine extractDirName

  subroutine extractFileSize(line, fileSize)
    character(len=*), intent(in) :: line
    integer, intent(out) :: fileSize
    integer :: pos

    pos = index(line, ' ')
    
    read(line(1:pos-1), *) fileSize

  end subroutine extractFileSize


  subroutine search(indexToDir, searchName, indexSearchDir, indexLastDir)
    character(len=*), intent(in) :: indexToDir(:)
    character(len=*), intent(in) :: searchName
    integer, intent(in) :: indexLastDir
    integer, intent(out) :: indexSearchDir
    integer :: i

    indexSearchDir = -1
    do i = 1, indexLastDir
      if (indexToDir(i) == searchName) then 
        indexSearchDir = i
        return
      end if 
    end do

  end subroutine search

end program main


  