;; chez-presentation.ss
(import (chezscheme))

(define (pause-for-audience)
  (display "\n>>> Press [ENTER] to reveal the compiler's work <<<\n")
  (get-line (current-input-port)))

(define (print-slide-title title)
  (display "\n=================================================================\n")
  (display title)
  (display "\n=================================================================\n"))

(display "\nWelcome to the Chez Scheme Compiler Deep Dive!\n")
(pause-for-audience)

;; -----------------------------------------------------------------
;; ACT 1: Macros - The Programmable Programming Language
;; -----------------------------------------------------------------
(print-slide-title "ACT 1: Macros & The Expander")
(display "Scheme allows us to invent new syntax. Let's create a 'while' loop.\n")
(display "To the compiler, our custom 'while' loop doesn't exist; it gets desugared.\n\n")

(define-syntax while
  (syntax-rules ()
    [(_ condition body ...)
     (let loop ()
       (when condition
         body ...
         (loop)))]))

(define macro-code 
  '(while (< x 10)
     (display x)
     (set! x (+ x 1))))

(display "--- The code we wrote:\n")
(pretty-print macro-code)

(pause-for-audience)

(display "--- What the expander turns it into (Core Scheme):\n")
(pretty-print (expand macro-code))


;; -----------------------------------------------------------------
;; ACT 2: The Optimizer & Assembly Code
;; -----------------------------------------------------------------
(pause-for-audience)
(print-slide-title "ACT 2: The Optimizer & Assembly Code")
(display "Chez Scheme is an AOT compiler. It goes straight to machine code.\n")
(display "Let's look at a messy function with dead code and redundant math.\n\n")

(define messy-code 
 '(define (do-math n)
    (let ([is-valid #t]
          [multiplier (* 5 10)])
      (if is-valid
          (+ n multiplier)
          (display "DEAD CODE: This will never run!")))))

(display "--- The unoptimized code:\n")
(pretty-print messy-code)

(pause-for-audience)

(display "--- Let's flip the internal compiler switch to see the raw machine code:\n")
(display "Notice: There is no multiplication, no branching, and no strings.\n")
(display "Just an instruction adding 50 to our input!\n\n")

;; Chez Scheme Magic Spell: 
;; We set the internal assembly-output parameter to #t, then dynamically
;; evaluate (compile) the code so it spits out the assembly to the console.
(parameterize ([#%$assembly-output #t])
  (eval messy-code (interaction-environment)))


;; -----------------------------------------------------------------
;; ACT 3: Type Optimization (Fixnums)
;; -----------------------------------------------------------------
(pause-for-audience)
(print-slide-title "ACT 3: Dynamic vs. Static Types")
(display "Generic math requires runtime type checking.\n")
(display "Let's compare generic addition vs. Fixnum (integer-only) addition.\n\n")

(display "--- Assembly for Generic (+ a b) ---\n")
(display "Notice the extra instructions to check if the inputs are integers.\n")
(parameterize ([#%$assembly-output #t])
  (eval '(define (add-generic a b) (+ a b)) (interaction-environment)))

(pause-for-audience)

(display "\n--- Assembly for Fixnum (fx+ a b) ---\n")
(display "Notice how clean it is! It compiles down to a raw CPU ADD instruction.\n")
(parameterize ([#%$assembly-output #t])
  (eval '(define (add-fast a b) (fx+ a b)) (interaction-environment)))


;; -----------------------------------------------------------------
;; ACT 4: Tooling - Trace and Time
;; -----------------------------------------------------------------
(pause-for-audience)
(print-slide-title "ACT 4: Profiling & Tracing")
(display "Chez includes built-in tools for debugging and profiling.\n\n")

(define (factorial n)
  (if (<= n 1)
      1
      (* n (factorial (- n 1)))))

(display "--- Tracing a function call ---\n")
(display "Let's trace (factorial 4):\n")
(trace factorial)
(factorial 4)
(untrace factorial)

(display "\n--- Timing execution ---\n")
(display "Let's time how long it takes to calculate factorial 50000:\n")
(time (begin (factorial 50000) (void)))

(display "\n=================================================================\n")
(display "End of Presentation.\n")

(exit)