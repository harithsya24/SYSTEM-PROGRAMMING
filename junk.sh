#!/bin/bash 

home_directory="$HOME"
readonly hide_junk="$home_directory/.junk"
mkdir -p "$hide_junk"

DESTINATION="/$HOME/.junk"
filename="$1"
file_names=(*)

usage(){
 cat <<EOF
Usage: $(basename "$0") [-hlp] [list of files]
  -h: Display help.
  -l: List junked files.
  -p: Purge all files.
  [list of files] with no other arguments to junk those files.
EOF
     exit 0
}

delete(){
         mv "$filename"* "$DESTINATION" 2>/dev/null
         mv "$filename".* "$DESTINATION" 2>/dev/null
 }


if [ "$#" -eq 0 ]; then
    usage
fi


argument="$1"

if [ "${argument:0:1}" = "-" ]; then
   if [ "$#" -gt 1 ]; then
       flag_found=false
       for arg in "$@"; do
           if [ "${arg:0:1}" = "-" ]; then
               flag_found=true
               break
           fi
       done
     
       if [ "$flag_found" = true ]; then
           echo "Error: Too many options enabled."
           usage
       fi
   fi
   
   while getopts ":hlp" opt; do
       case $opt in
           h) usage ;;
           l) ls -lAF "$DESTINATION" ;;
           p) shopt -s dotglob
              rm -rf "$HOME/.junk"/*
              shopt -u dotglob ;;
           \?) 
               echo "Error: Unknown option '-${OPTARG}'.">&2
               usage
               ;;
       esac
   done  
else 
    for item in "$@"; do
       if [ -e "$item" ]; then    
           mv "$item"* "$DESTINATION" 2>/dev/null
           mv "$item".* "$DESTINATION" 2>/dev/null
       else
          echo "Warning: '$item' not found."                                
       fi
    done
fi

