#!/bin/bash
#The explanation:

#https://unix.stackexchange.com/questions/78933/rsync-mkstemp-failed-invalid-argument-22-with-davfs-mount-of-box-com-cloud



# Mount cloud filesystem.
mount /media/dfs-cloudiaa/

#Move to the Workspace root dir.
cd /srv/share/Workspace


#Lets backup altium dir:

rsync -C -rltgoDvn --update --delete --exclude=Projects/Backups/ --exclude=Project\ Outputs*  --exclude=History --exclude=__Previews --exclude=Project\ Logs* --exclude-from=/srv/share/Workspace/tools/sysadmin/scripts/rsync_exclude.lst /srv/share/Workspace/Altium/ /media/dfs-cloudiaa/Workspace/Altium



#Curso RPi3 Folder:

rsync -C -rltgoDvn --update --delete --exclude-from=CursoRPI3/exclude.lst --exclude=Projects/Backups/  /srv/share/Workspace/CursoRPI3/ /media/dfs-cloudiaa/Workspace/CursoRPI3


#Workstation Folder:
rsync -C -rltgoDvn --update --delete --exclude-from=Workstation/exclude.lst --exclude=Projects/Backups/  /srv/share/Workspace/Workstation/ /media/dfs-cloudiaa/Workspace/Workstation
