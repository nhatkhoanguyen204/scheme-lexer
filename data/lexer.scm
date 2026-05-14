; Lexer for Scheme. The following is the lexical specification that it
; handles:
;
; <token> --> <identifier> | <boolean> | <number>
;     | <character> | <string> | ( | ) | #( | ' | ` | , | ,@ | .
; <delimiter> --> <whitespace> | ( | ) | " | ;
; <whitespace> --> <space or newline>
; <comment> --> ; <all subsequent characters up to a line break>
; <atmosphere> --> <whitespace> | <comment>
; <intertoken space> --> <atmosphere>*
;
; <identifier> --> <initial> <subsequent>*
;     | <peculiar identifier>
; <initial> --> <letter> | <special initial>
; <letter> --> [a-z]
;
; <special initial> --> ! | $ | % | & | * | / | : | < | =
;     | > | ? | ^ | _ | ~
; <subsequent> --> <initial> | <digit> | <special subsequent>
; <digit> --> [0-9]
; <special subsequent> --> + | - | . | @
; <peculiar identifier> --> + | - | ...
;
; <boolean> --> #t | #f
; <character> --> #\ <any character> | #\ <character name>
; <character name> --> space | newline
;
; <string> --> " <string element>* "
; <string element> --> <any character other than " or \>
;     | \" | \\
;
; <number> --> <integer> | <decimal>
; <integer> --> <sign> <digit>+
; <decimal> --> <sign> <digit>+ . <digit>*
;     | <sign> . <digit>+
;
; <sign> --> <empty> | + | -
;
; Project UID 7e390a38edc65081bf76ab8edd67fe9d208befb9

(load "distribution.scm")

;;;;;;;;;;;;;;;;;;;

; Removes whitespace and comments from the input stream.
(define (discard-atmosphere)
  (let ((next-char (peek-char)))
    (cond ((eof-object? next-char)) ; eof - just return
          ((char-whitespace? next-char) ; whitespace
           (read-char) ; discard it
           (discard-atmosphere)) ; get rid of remaining atmosphere
          ((char=? next-char #\;) ; comment
           (clear-line) ; discard it
           (discard-atmosphere)) ; get rid of remaining atmosphere
          ; else not atmosphere, so do nothing
    )
  )
)

;;;;;;;;;;;;;;;;;;;

; Read a string token.
(define (read-string)
  (discard-atmosphere) ; remove leading whitespace or comments
  (if (read-start #\" "not a string") ; string must start with "
      (read-string-tail '()) ; call helper function below
  )
)

; Read the rest of a string literal.
(define (read-string-tail read-so-far)
  (let ((next-char (get-non-eof-char))) ; read a single char
    (cond ((char=? next-char #\") ; end of string
           ; return a string token
           (token-make 'string (list->string (reverse read-so-far))))
          ((char=? next-char #\\) ; start of escape sequence
           ; read the rest of the escape sequence and recurse
           (read-string-tail (cons (read-escaped) read-so-far)))
          ; complete this procedure
    )
  )
)

; Read the rest of an escape sequence.
(define (read-escaped)
  (let ((escaped-char (get-non-eof-char)))
    (if (or (char=? escaped-char #\") (char=? escaped-char #\\))
        escaped-char
        (error (string-append "unrecognized escape sequence \\"
                              (string escaped-char)))
    )
  )
)

;;;;;;;;;;;;;;;;;;;

; Read a boolean token.
(define (read-boolean)
  (discard-atmosphere) ; remove leading whitespace or comments
  (if (read-start #\# "not a boolean") ; boolean starts with #
      (read-boolean-tail)
  )
)

; Read the rest of a boolean literal.
(define (read-boolean-tail)
  '() ; replace with your code
)

;;;;;;;;;;;;;;;;;;;

; Read a character token.
(define (read-character)
  (discard-atmosphere) ; remove leading whitespace or comments
  (if (and (read-start #\# "not a character")  ; character must start
           (read-start #\\ "not a character")) ; with #\
      (read-character-tail)
  )
)

; Read the rest of a character literal.
(define (read-character-tail)
  '() ; replace with your code
)


;;;;;;;;;;;;;;;;;;;

; Determine if the given character is a sign character.
(define (sign? char)
  (or (char=? char #\+) (char=? char #\-))
)

; Determine if the given character is a digit.
(define (digit? char)
  (and (char>=? char #\0) (char<=? char #\9))
)

; Read a number token.
(define (read-number)
  (discard-atmosphere) ; remove leading whitespace or comments
  ; add your code here
)


;;;;;;;;;;;;;;;;;;;


; Read an identifier token.
(define (read-identifier)
  (discard-atmosphere) ; remove leading whitespace or comments
  ; add your code here
)


;;;;;;;;;;;;;;;;;;;


; Read a punctuator token (i.e. one of ( ) #( . ' ` , ,@ ).
(define (read-punctuator)
  (discard-atmosphere) ; remove leading whitespace or comments
  ; add your code here
)


;;;;;;;;;;;;;;;;;;;

; Read a token, which can be a boolean, character, string, identifier,
; number, or punctuator. Discards whitespace and comments.
(define (read-token)
  (discard-atmosphere) ; remove leading whitespace or comments
  (let ((next-char (peek-char)))
    (cond ((eof-object? next-char) ; eof
           next-char) ; just return eof
          ; complete this procedure
          (else
           (error "unknown start of token" next-char))
    )
  )
)
