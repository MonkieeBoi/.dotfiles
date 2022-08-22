"set theming
let g:lightline = {'colorscheme': 'nord'}
set laststatus=2
colorscheme nord

"highlights searchs
set hlsearch

"highlights while searching
set incsearch

"sets default clipboard to system clipboard -- i don't think this actually works
set clipboard=unnamedplus

"set tab to 4 spaces
set tabstop=4
set softtabstop=4
set shiftwidth=4

"makes tabs spaces - which is better for some reason
set expandtab
set autoindent

"idk what this does
set fileformat=unix

"autocomplete, i think ctrl+n does something related to this
set wildmode=longest,list,full

"i give up commenting
syntax on
set encoding=utf-8

set nu rnu


" Toggle bg - for when you're too lazy to switch to non-transparent
let t:is_transparent = 0
function! Toggle_transparent_background()
  if t:is_transparent == 0
    hi Normal guibg=#111111 ctermbg=black
    let t:is_transparent = 1
  else
    hi Normal guibg=NONE ctermbg=NONE
    let t:is_transparent = 0
  endif
endfunction
nnoremap <F1> :call Toggle_transparent_background()<CR>
