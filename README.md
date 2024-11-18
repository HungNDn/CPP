Git Usage: 

/* */Quy Trinh Xu Ly Xung Dot /* */

git stash : luu lai thay doi code tren local.
git fetch : fetch lai code moi nhat tren repo.(No auto merge) or git pull  : pull code moi nhat tren repo.(Auto merge)
git stash pop: Push lai code vua luu cua lenh git stash ra.

Khi Nay se co 2 loai code : Code tren local -- Code repo.(Neu khac nhau => Conflict)

git mergetool : Giai quyet conlict.
find . -name "*.orig" | xargs rm -f : Xoa file du thua sau khi giai quyet conflict xong.
git add . : add commit 
git commit : commit 

/* */ Quy Trinh Chinh Sua Lai Commit Khi Da Push To Repo /* */

git commit --amend

/* */ Quy Trinh Di Chuyen Ve Commit Truoc Voi Git Reset /* */

git reset     --hard HEAD     (going back to HEAD) 
git reset     --hard HEAD^     (going back to the commit before HEAD) 
git reset     --hard HEAD~1     (equivalent to "^") 
git reset     --hard HEAD~2     (going back two commits before HEAD)

git reset --hard : Quay Ve commit duoc chi dinh va xoa toan bo lich su cua cac commit sau no, xoa luon nhuwng thay doi trong file luc chung ta lam viec.
git reset --soft : Quay Ve commit duoc chi dinh va xoa toan bo lich su cua cac commit sau no nhung van giu nguyen nhung thay doi trong file trong luc chung ta lam viec.

VD: A->B->C->D 
git reset --hard B => lich su commit C, D se mat, local luc nay se la commit B nguyen goc.
git reset --soft B => lich su commit C, D se mat, local luc nay se la commit B bi thay doi khi chung ta thay doi code truoc do.

- Voi TH da day commit code toi repo: 
git reset  --hard  HEAD
git clean -f  -d
git push -f  <remote-name-origin> <branch-name-develop>

/* */ Quy Trinh Di Chuyen Ve Commit Truoc Voi Git Revert /* */

git revert : Quay ve commit nay duoc chi dinh bang cach tao ra ban sao, giu nguyen lich su commit truoc do.
VD: A->B->C->D
git revert C => A->B->C->D->D->C'.(D' la ban sao cua D, C' la ban sao cua C)

/* */ Xem Lich Su Commit /* */

git log --oneline –graph 

/* */ Undo Git Add /* */

git restore --staged filename

/* */ Git cherry-pick /* */


VD: Lay 1 commit nhanh A chuyen vao nhanh B
git checkout master
git cherry-pick feature-A~1

# Hoặc chúng ta có thể chỉ định hash commit
git cherry-pick C2 // Commit C2 la cua nhanh feature-A vi tri commit sau HEAD 1 commit

VD: 1 lan commit cho ca 2 branch
# Đang ở branch-X, thực hiện commit để tạo ra commit A
git add -A
git commit -m " finish commit A"

# Checkout sang branch Y và dùng cherry-pick nào
git checkout branch-Y
git cherry-pick branch-X


Cmd + Shift + period (.) để hiển thị các tệp ẩn trên máy Mac của bạn.

https://github.com/settings/tokens

git remote add origin https://token@github.com/HungNDn/C-_Learning.git

git push https://token@github.com/HungNDn/C-_Learning.git
